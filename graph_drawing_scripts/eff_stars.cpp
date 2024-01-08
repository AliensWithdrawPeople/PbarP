#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int eff_stars()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // ********************* Start of Data ********************* //

    std::vector<double> energy = {940.166, 940.608, 941.882, 950.359, 944.817, 950.15, 945.461, 950.29, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 949.995, 950.945}; // MeV
    
    std::vector<double> eff_ge = {0.1897, 0.1987, 0.1965, 0.0721, 0.2136, 0.085, 0.2064, 0.0828, 0.2014, 0.1982, 0.1994, 0.2012, 0.1905, 0.186, 0.092, 0.0567}; // nb
    std::vector<double> eff_ge_error = {0.0005, 0.0005, 0.0005, 0.0002, 0.0005, 0.0002, 0.0005, 0.0002, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0003, 0.0002}; // nb
    std::vector<double> eff_gm = {0.175, 0.1852, 0.1826, 0.1043, 0.2021, 0.1204, 0.1963, 0.1209, 0.189, 0.1839, 0.189, 0.1901, 0.185, 0.1794, 0.124, 0.0948}; // nb
    std::vector<double> eff_gm_error = {0.0005, 0.0005, 0.0005, 0.0003, 0.0005, 0.0003, 0.0005, 0.0003, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0003, 0.0003}; // nb

    std::vector<double> eff_ge_z_cut_10cm = {0.192, 0.2012, 0.1988, 0.0736, 0.2158, 0.087, 0.2091, 0.0844, 0.2035, 0.2012, 0.2022, 0.2045, 0.1932, 0.1887, 0.0935, 0.058}; // nb
    std::vector<double> eff_ge_error_z_cut_10cm = {0.0005, 0.0005, 0.0005, 0.0002, 0.0005, 0.0003, 0.0005, 0.0002, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0003, 0.0002}; // nb
    std::vector<double> eff_gm_z_cut_10cm = {0.1789, 0.1896, 0.1871, 0.1091, 0.2066, 0.1255, 0.2017, 0.1263, 0.1936, 0.1891, 0.1943, 0.1958, 0.1906, 0.1848, 0.1286, 0.0993}; // nb
    std::vector<double> eff_gm_error_z_cut_10cm = {0.0005, 0.0005, 0.0005, 0.0003, 0.0005, 0.0003, 0.0005, 0.0003, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0004, 0.0003}; // nb
    // ********************* End of Data ********************* //

    TGraphErrors ge(energy.size(), energy.data(), eff_ge.data(), 
                                            zeroes.data(), eff_ge_error.data());
    TGraphErrors gm(energy.size(), energy.data(), eff_gm.data(), 
                                            zeroes.data(), eff_gm_error.data());

    TGraphErrors ge_z_cut_10cm(energy.size(), energy.data(), eff_ge_z_cut_10cm.data(), 
                                            zeroes.data(), eff_ge_error_z_cut_10cm.data());
    TGraphErrors gm_z_cut_10cm(energy.size(), energy.data(), eff_gm_z_cut_10cm.data(), 
                                            zeroes.data(), eff_gm_error_z_cut_10cm.data());

    ge.SetMarkerColor(kMagenta);
    ge.SetName("eff_ge");
    ge.GetXaxis()->SetTitle("E_{beam}, MeV");
    ge.GetYaxis()->SetTitle("#varepsilon_{e^{+}e^{-} #rightarrow p#bar{p}}");
    ge.SetTitle("|z| < 8");

    gm.SetMarkerColor(kBlack);
    gm.SetName("eff_gm");
    gm.GetXaxis()->SetTitle("E_{beam}, MeV");
    gm.GetYaxis()->SetTitle("#varepsilon_{e^{+}e^{-} #rightarrow p#bar{p}}");
    gm.SetTitle("|z| < 8");

    ge_z_cut_10cm.SetMarkerColor(kMagenta);
    ge_z_cut_10cm.SetMarkerStyle(22);
    ge_z_cut_10cm.SetName("ge_z_cut_10cm");
    ge_z_cut_10cm.GetXaxis()->SetTitle("E_{beam}, MeV");
    ge_z_cut_10cm.GetYaxis()->SetTitle("#varepsilon_{e^{+}e^{-} #rightarrow p#bar{p}}");
    ge_z_cut_10cm.SetTitle("|z vertex| < 10");

    gm_z_cut_10cm.SetMarkerColor(kBlack);
    gm_z_cut_10cm.SetMarkerStyle(22);
    gm_z_cut_10cm.SetName("gm_z_cut_10cm");
    gm_z_cut_10cm.GetXaxis()->SetTitle("E_{beam}, MeV");
    gm_z_cut_10cm.GetYaxis()->SetTitle("#varepsilon_{e^{+}e^{-} #rightarrow p#bar{p}}");
    gm_z_cut_10cm.SetTitle("|z vertex| < 10");
    
    ge.DrawClone("AP");
    gm.DrawClone("same P");

    ge_z_cut_10cm.DrawClone("same P");
    gm_z_cut_10cm.DrawClone("same P");

    canv.DrawClone();
    return 0;
}