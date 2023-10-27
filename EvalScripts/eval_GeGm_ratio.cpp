#include <memory>
#include <iostream>

#include <TTree.h>
#include <TH1D.h>
#include <TFitResult.h>
#include <TFitResultPtr.h>
#include <TFractionFitter.h>
#include <TFile.h>
#include <TObjArray.h>
#include <TCanvas.h>
#include <TF1.h>

// int eval_GeGm_ratio()
int eval_GeGm_ratio(std::string dist, std::string exp_filename, std::string MC_filename_Ge, std::string MC_filename_Gm)
{ 
    // std::string dist = "C:/work/Science/BINP/PbarP/tr_ph/GeGmResults/season_HIGH2019_elabel975_80603_GeGm_Ratio_Res.root";
    // std::string exp_filename = "C:/work/Science/BINP/PbarP/tr_ph/root_files/Exp/final/energy_975MeV/season2019_coll.root";
    // std::string MC_filename_Ge = "C:/work/Science/BINP/PbarP/tr_ph/root_files/MC/final/energy_972.92MeV/season2019_coll_Ge1_Ge0_run000109.root";
    // std::string MC_filename_Gm = "C:/work/Science/BINP/PbarP/tr_ph/root_files/MC/final/energy_972.92MeV/season2019_coll_Ge0_Ge1_run000209.root";
    auto file = new TFile(dist.c_str(), "recreate");
    TCanvas canv("canv");

    auto expFile = TFile::Open(exp_filename.c_str());
    auto mcFile_Ge = TFile::Open(MC_filename_Ge.c_str());
    auto mcFile_Gm = TFile::Open(MC_filename_Gm.c_str());
    auto exp = expFile->Get<TTree>("pbarp");
    auto MC_Ge = mcFile_Ge->Get<TTree>("pbarp");
    auto MC_Gm = mcFile_Gm->Get<TTree>("pbarp");

    auto exp_distr = new TH1D("exp_distr", "exp_distr", 50, -1, 1);
    auto MC_Ge_distr = new TH1D("MC_Ge_distr", "MC_Ge_distr", 50, -1, 1);
    auto MC_Gm_distr = new TH1D("MC_Gm_distr", "MC_Gm_distr", 50, -1, 1);

    exp->Draw("cos(theta_v) >> exp_distr", "", "goff");
    MC_Ge->Draw("cos(theta_v) >> MC_Ge_distr", "", "goff");
    MC_Gm->Draw("cos(theta_v) >> MC_Gm_distr", "", "goff");
    MC_Gm_distr->Scale(4./3. * MC_Ge_distr->Integral() / MC_Gm_distr->Integral());
    file->cd();
    TObjArray *mc = new TObjArray(2);
    mc->Add(MC_Ge_distr);
    mc->Add(MC_Gm_distr);

/* TFractionFitter block */
    // TFractionFitter* fit = new TFractionFitter(exp_distr, mc);
    // fit->Constrain(0,0.0,1.0); 
    // // fit->Constrain(1,0.0,1.0);

    // auto width = exp_distr->GetBinWidth(0);
    // auto left_boundary = exp_distr->GetBinCenter(0) - width / 2;
    // Int_t left_constraint = int((-0.5 - left_boundary) / width);
    // Int_t right_constraint = int((0.5 - left_boundary) / width);
    // std::cout << width << " : " << left_constraint << " : " << right_constraint << std::endl;
    // fit->SetRangeX(left_constraint, right_constraint);
    // Int_t status = fit->Fit();

    // auto prob = fit->GetProb();
    // auto chi2 = fit->GetChisquare();
    // auto ndf = fit->GetNDF();
    // double Ge_frac, Ge_frac_err;
    // double Gm_frac, Gm_frac_err;
    // fit->GetResult(0, Ge_frac, Ge_frac_err);
    // fit->GetResult(1, Gm_frac, Gm_frac_err);
    // auto result = (TH1D*) fit->GetPlot();
/* TFractionFitter block */

    auto fit_func = new TF1("sum_mc_angular_distribution", [&](double *x, double *par){
        return par[0] * (par[1] * MC_Ge_distr->Interpolate(x[0]) + par[2] * MC_Gm_distr->Interpolate(x[0]));
    }, -1, 1, 3);
    fit_func->SetParameters(exp_distr->Integral() / (MC_Ge_distr->Integral()), 0.5, 0.5);
    fit_func->SetParameters(0.2, 0.5, 0.3);
    fit_func->SetParLimits(0, 0., 100.);
    fit_func->SetParLimits(1, 0., 100.);
    fit_func->FixParameter(2, 1);
    auto fit_res = exp_distr->Fit(fit_func, "SPME", "", -0.5, 0.5);

    auto status = fit_res->CovMatrixStatus() ;
    double Ge_frac = fit_res->Parameter(1);
    double Gm_frac = fit_res->Parameter(2);
    double Ge_frac_err = fit_res->ParError(1);
    double Gm_frac_err = fit_res->ParError(2);
    auto prob = fit_res->Prob();
    auto chi2 = fit_res->Chi2();
    auto ndf = fit_res->Ndf();

    std::cout << "fit covariance matrix status: " << status << std::endl;
    std::cout << "fit prob: " << prob << std::endl;
    std::cout << "fit chi2 / ndf: " << chi2 << " / " << ndf << std::endl;
    std::cout << "Ge^2: " << Ge_frac << " +/- " << Ge_frac_err << std::endl;
    std::cout << "Gm^2: " << Gm_frac << " +/- " << Gm_frac_err << std::endl;
    fit_func->Write();
    fit_func->SetNpx(1000);
    auto result = fit_func->GetHistogram();

    MC_Gm_distr->Scale(Gm_frac * exp_distr->Integral() / MC_Gm_distr->Integral());
    MC_Ge_distr->Scale(Ge_frac * exp_distr->Integral() / MC_Ge_distr->Integral());

    MC_Gm_distr->SetLineColor(kRed);
    MC_Ge_distr->SetLineColor(kBlue);

    result->SetName("FitResult");
    exp_distr->DrawClone("Ep");
    result->DrawClone("same");
    MC_Gm_distr->DrawClone("same");
    MC_Ge_distr->DrawClone("same");

    result->Write();
    exp_distr->Write();
    MC_Ge_distr->Write();
    MC_Gm_distr->Write();
    canv.DrawClone();
    canv.Write();
    file->Save();

    return fit_res->IsValid();
}