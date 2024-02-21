#include <iostream>
#include <string.h> 
#include <algorithm> 

#include <TEfficiency.h>
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TFitResult.h>
#include <TFitResultPtr.h>


/// @brief Compute a ratio of track efficiencies in MC and EXP (MC/EXP). 
/// @param exp_filename Full path of root-file with experimental data.
/// @param MC_filename_Ge Full path of root-file with MC data (Ge = 1, Gm = 0).
/// @param MC_filename_Gm Full path of root-file with MC data (Ge = 0, Gm = 1).
/// @param result_file_name Full path of dist file.
/// @param result_name Name of resulting graphs.
/// @param bin_number Number of bins for efficiencies' ratio histogram
/// @return Histogram where bin content is eff in the corresponding bin and 
// TH1D* get_track_eff(std::string exp_filename, std::string MC_filename_Ge, std::string MC_filename_Gm, int bin_number = 50) 
TH1D* get_track_eff(std::string exp_filename, std::string MC_filename_Ge, std::string MC_filename_Gm, std::string result_file_name, std::string result_name, std::string Elabel, int bin_number = 50) 
{
    // Elabel: 980_99550
    // std::string exp_filename = "C:/work/Science/BINP/PbarP/tr_ph/root_files/Exp/final/energy_980MeV/season2021_coll_tr_eff.root";
    // std::string MC_filename_Ge = "C:/work/Science/BINP/PbarP/tr_ph/root_files/MC/final/energy_980.25MeV/season2021_coll_tr_eff_Ge0_Ge1_run000217.root";
    // std::string MC_filename_Gm = "C:/work/Science/BINP/PbarP/tr_ph/root_files/MC/final/energy_980.25MeV/season2021_coll_tr_eff_Ge1_Ge0_run000117.root";
    // std::string result_file_name = "test.root";
    // std::string result_name = "test";
    // std::string Elabel = "980_99550";

    auto expFile = TFile::Open(exp_filename.c_str());
    auto mcFile_Ge = TFile::Open(MC_filename_Ge.c_str());
    auto mcFile_Gm = TFile::Open(MC_filename_Gm.c_str());
    auto exp = expFile->Get<TTree>("pbarp");
    auto MC_Ge = mcFile_Ge->Get<TTree>("pbarp");
    auto MC_Gm = mcFile_Gm->Get<TTree>("pbarp");


    TH1D exp_both("exp_both", "exp_both", bin_number, -1, 1);    
    TH1D exp_all ("exp_all", "exp_all", bin_number, -1, 1);    

    TH1D ge_both("ge_both", "ge_both", bin_number, -1, 1);    
    TH1D ge_all("ge_all", "ge_all", bin_number, -1, 1);   

    auto gm_both = new TH1F("gm_both", "gm_both", bin_number, -1, 1);    
    auto gm_all = new TH1F("gm_all", "gm_all", bin_number, -1, 1);   

    TH1D mom_exp("mom_exp", "mom_exp", 200, 0, 1000);    
    exp->Draw("antiproton_mom >> mom_exp", "", "goff");
    auto fit_res1 = mom_exp.Fit("gaus", "SLME0", "goff", mom_exp.GetMean() - 2 * mom_exp.GetRMS(), mom_exp.GetMean() + 1 * mom_exp.GetRMS());
    auto fit_res2 = mom_exp.Fit("gaus", "SLME0", "goff", fit_res1->Parameter(1) - 2 * fit_res1->Parameter(2), fit_res1->Parameter(1) + 1 * fit_res1->Parameter(2));
    double left_bound = fit_res2->Parameter(1) - 3 * fit_res2->Parameter(2);
    double right_bound = fit_res2->Parameter(1) + 3 * fit_res2->Parameter(2);
    std::string mom_cut = std::to_string(left_bound) + " < antiproton_mom && antiproton_mom < " + std::to_string(right_bound);
    std::cout << mom_cut << std::endl;
    exp->Draw("cos(antiproton_theta) >> exp_all", mom_cut.c_str(), "goff");
    MC_Ge->Draw("cos(antiproton_theta) >> ge_all", mom_cut.c_str(), "goff");
    MC_Gm->Draw("cos(antiproton_theta) >> gm_all", mom_cut.c_str(), "goff");

    exp->Draw("cos(antiproton_theta) >> exp_both", ("found_both && " + mom_cut).c_str(), "goff");
    MC_Ge->Draw("cos(antiproton_theta) >> ge_both", ("found_both && " + mom_cut).c_str(), "goff");
    MC_Gm->Draw("cos(antiproton_theta) >> gm_both", ("found_both && " + mom_cut).c_str(), "goff");

    ge_both.Add(gm_both, 1);
    ge_all.Add(gm_all, 1);
    
    TCanvas canv("canv");
    std::cout << "is EXP hists consistent: " << TEfficiency::CheckConsistency(exp_both, exp_all) << std::endl;
    auto exp_eff = new TEfficiency(exp_both, exp_all);
    exp_eff->SetName("exp_eff");
    exp_eff->SetTitle(("Track reco efficiency, Elabel = " + Elabel + "; cos(#theta) ; #varepsilon").c_str());

    std::cout << "is MC hists consistent: " << TEfficiency::CheckConsistency(ge_both, ge_all) << std::endl;
    auto mc_eff = new TEfficiency(ge_both, ge_all);
    mc_eff->SetName("mc_eff");
    mc_eff->SetTitle("mc_eff");
    mc_eff->SetMarkerColor(kRed);
    exp_eff->DrawClone();
    mc_eff->DrawClone("same");
    canv.DrawClone();

    auto exp_tmp = new TH1D("exp_tmp", "", bin_number, -1, 1);
    auto mc_tmp = new TH1D("mc_tmp", "", bin_number, -1, 1);
    for(int i = 0; i < bin_number; i++)
    {
        exp_tmp->SetBinContent(i, (exp_eff->GetEfficiency(i) > 1e-3)? exp_eff->GetEfficiency(i) : 1);
        exp_tmp->SetBinError(i, std::max(exp_eff->GetEfficiencyErrorUp(i), exp_eff->GetEfficiencyErrorLow(i)));

        mc_tmp->SetBinContent(i, (mc_eff->GetEfficiency(i) > 1e-3)? mc_eff->GetEfficiency(i) : 1);
        mc_tmp->SetBinError(i, std::max(mc_eff->GetEfficiencyErrorUp(i), mc_eff->GetEfficiencyErrorLow(i)));
    }
    mc_tmp->Draw();
    // mc_tmp->Sumw2();
    // exp_tmp->Sumw2();
    mc_tmp->Divide(exp_tmp);
    mc_tmp->SetTitle(("MC to EXP efficiency ratio, Elabel = " + Elabel + "; cos(#theta) ; #varepsilon^{(MC)}/#varepsilon^{(EXP)}").c_str());

    auto res_file = new TFile(result_file_name.c_str(), "recreate");
    canv.SetName(("eff_" + result_name).c_str());
    canv.Write();
    mc_tmp->SetTitle("MC to EXP efficiency ratio ; cos(#theta) ; #varepsilon^{(MC)}/#varepsilon^{(EXP)}");
    // mc_tmp->SetName(("ratio_" + result_name).c_str());

    TCanvas canv2("ratio");
    mc_tmp->DrawClone("E");
    canv2.DrawClone();
    canv2.SetName(("ratio_" + result_name).c_str());
    canv2.Write();

    // mc_tmp->Write();
    res_file->Save();
    return mc_tmp;
}
