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


int eval_GeGm_ratio(std::string dist, std::string exp_filename, std::string MC_filename_Ge, std::string MC_filename_Gm)
{ 
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

    TFractionFitter* fit = new TFractionFitter(exp_distr, mc);
    fit->Constrain(0,0.0,1.0); 
    fit->Constrain(1,0.0,1.0);
    Int_t left_boundary = 0;
    Int_t right_boundary = 0;
    exp_distr->GetBinWithContent(cos(1.), left_boundary, 0, exp_distr->GetNbinsX(), 1e-2);
    exp_distr->GetBinWithContent(cos(3.1415 - 1.), right_boundary, 0, exp_distr->GetNbinsX(), 1e-2);
    fit->SetRangeX(left_boundary, right_boundary);
    Int_t status = fit->Fit();

    double Ge_frac, Ge_frac_err;
    double Gm_frac, Gm_frac_err;
    fit->GetResult(0, Ge_frac, Ge_frac_err);
    fit->GetResult(1, Gm_frac, Gm_frac_err);
    std::cout << "fit prob: " << fit->GetProb() << std::endl;
    std::cout << "fit chi2 / ndf: " << fit->GetChisquare() << " / " << fit->GetNDF() << std::endl;
    std::cout << "Ge^2: " << Ge_frac << " +/- " << Ge_frac_err << std::endl;
    std::cout << "Gm^2: " << Gm_frac << " +/- " << Gm_frac_err << std::endl;

    TH1D* result = (TH1D*) fit->GetPlot();
    result->SetName("FitResult");
    exp_distr->DrawClone("Ep");
    result->DrawClone("same");

    result->Write();
    exp_distr->Write();
    MC_Ge_distr->Write();
    MC_Gm_distr->Write();
    canv.DrawClone();
    file->Save();

    return status;
}