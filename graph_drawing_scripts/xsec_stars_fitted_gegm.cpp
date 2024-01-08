#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int xsec_stars_fitted_gegm()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // ********************* Start of Data ********************* //

    std::vector<double> energy = {940.166, 940.608, 941.882, 950.359, 944.817, 950.15, 945.461, 950.29, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 949.995, 950.945}; // MeV
    std::vector<double> xsec = {0.2398, 0.287, 0.3019, 0.3206, 0.3318, 0.3617, 0.3458, 0.3159, 0.2519, 0.2651, 0.2921, 0.3019, 0.317, 0.3423, 0.2842, 0.2563}; // nb
    std::vector<double> xsec_err= {0.0388, 0.0399, 0.0479, 0.1101, 0.0378, 0.1047, 0.023, 0.0877, 0.0197, 0.0227, 0.0206, 0.0214, 0.017, 0.0197, 0.0678, 0.0934}; // nb
    // ********************* End of Data ********************* //

    TGraphErrors xsec_vs_energy_stars(energy.size(), energy.data(), xsec.data(), 
                                            zeroes.data(), xsec_err.data());
    xsec_vs_energy_stars.SetMarkerColor(kGreen);
    xsec_vs_energy_stars.SetName("xsec_vs_energy_stars");
    xsec_vs_energy_stars.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_stars.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_stars.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} annihilation events with fitted |Ge/Gm|^{2}");

    xsec_vs_energy_stars.DrawClone("AP");

    canv.DrawClone();
    return 0;
}