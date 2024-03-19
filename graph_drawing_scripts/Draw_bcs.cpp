#include <TFile.h>
#include <TGraphErrors.h>
#include <TRatioPlot.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TRoot.h>

#include <vector>


int Draw_bcs()
{
    // Setup: start
    // double k_stars = 0.5281996429;
    // double k_stars_error = 0.02415563611;
    // std::string filename = "bcs_pbarp_salnikov.root";

    double k_stars = 0.5739190183;
    double k_stars_error = 0.02354318059;
    std::string filename = "bcs_pbarp_salnikov_no_fs_interaction_new.root";

    // double k_stars = 0.8545;
    // double k_stars_error = 0.1043;
    // std::string filename = "bcs_pbarp_exp_gap_eff_fit.root";
    // Setup: end

    TCanvas canv;
    std::string fullFilename = "C:/work/Science/BINP/PbarP/Results/bcs/" + filename; 
    auto file = TFile::Open(fullFilename.c_str());
    auto vcs = file->Get<TGraphErrors>("vcs");
    auto bcs = file->Get<TGraphErrors>("bcs");
    auto f_vcs = file->Get<TF1>("f_vcs");
    auto f_bcs = file->Get<TF1>("f_bcs");

    int N_points = vcs->GetN();
    double x = 0;
    double y = 0;
    double f_y = 0;
    double yErr = 0;

    std::vector<double> xs = {};

    std::vector<double> xsec = {};
    std::vector<double> xsec_err = {};
    for(int i = 0; i < N_points; i++)
    {
        x = vcs->GetPointX(i);
        y = vcs->GetPointY(i) * (x < 1.910? k_stars : 1);
        yErr = sqrt((vcs->GetErrorY(i) * k_stars) * (vcs->GetErrorY(i) * k_stars) + (vcs->GetPointY(i) * k_stars_error) * (vcs->GetPointY(i) * k_stars_error));
        // yErr = vcs->GetErrorY(i);
        f_y = f_vcs->Eval(x);

        xs.push_back(x);
        xsec.push_back(y);
        xsec_err.push_back(yErr);
    }

    std::vector<double> zeroes(100, 0.0);
    TGraphErrors gr_vcs(xs.size(), xs.data(), xsec.data(), zeroes.data(), xsec_err.data());

    std::vector<double> babar_energy = {1.87825, 1.8825, 1.8875, 1.8925, 1.8975, 1.9025, 1.9075, 1.9125, 1.92, 1.93125, 1.94375, 1.95625, 1.96875};
    std::vector<double> babar_energy_err = {0.00175, 0.0025, 0.0025, 0.0025, 0.0025, 0.0025, 0.0025, 0.0025, 0.005, 0.00625, 0.00625, 0.00625, 0.00625};
    std::vector<double> babar_xsec = {0.534, 0.826, 0.705, 0.886, 0.938, 0.785, 0.937, 1.096, 0.862, 0.811, 0.887, 0.780, 0.850};
    std::vector<double> babar_xsec_err = {0.094, 0.106, 0.105, 0.121, 0.121, 0.128, 0.123, 0.135, 0.142, 0.084, 0.069, 0.072, 0.070};
    TGraphErrors gr_babar(babar_energy.size(), babar_energy.data(), babar_xsec.data(), babar_energy_err.data(), babar_xsec_err.data());

    gr_vcs.DrawClone("AP");
    f_vcs->DrawClone("same");

    // gr_babar.Draw("AP");
    // bcs->SetMarkerColor(kRed);
    // bcs->SetMarkerStyle(23);
    // bcs->SetLineColor(kRed);
    // bcs->DrawClone("P same");

    canv.DrawClone();

    return 0;
}