#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int xsec_bkg()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // season2019
    std::vector<double> nominal_energy_season2019 = {936, 945, 950, 955, 962.5, 975, 978, 987.5};
    std::vector<double> energy_season2019 = {936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81};
    std::vector<double> xsec_season2019 = {0.0063, 0.0113, 0.0066, 0.0079, 0.0057, 0.0076, 0.0044, 0.0097};
    std::vector<double> xsec_err_season2019 = {0.0018, 0.0022, 0.0018, 0.0025, 0.0017, 0.0014, 0.0031, 0.0021};
    TGraphErrors xsec_vs_energy_season2019(energy_season2019.size(), energy_season2019.data(), xsec_season2019.data(), 
                                            zeroes.data(), xsec_err_season2019.data());
    xsec_vs_energy_season2019.SetMarkerColor(kRed);
    xsec_vs_energy_season2019.SetName("xsec_vs_energy_season2019");
    xsec_vs_energy_season2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_season2019.GetYaxis()->SetTitle("#sigma^{(vis)}_{e^{+}e^{-} #rightarrow bkg}, nb");
    xsec_vs_energy_season2019.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} bkg in annihilation events");

    // season2020
    std::vector<double> nominal_energy_season2020 = {935, 945, 950, 960, 970};
    std::vector<double> energy_season2020 = {934.705, 945.461, 950.29, 960.252, 970.583};
    std::vector<double> xsec_season2020 = {0.0058, 0.0095, 0.0048, 0.0059, 0.0036};
    std::vector<double> xsec_err_season2020 = {0.0008, 0.001, 0.0007, 0.0008, 0.0006};
    TGraphErrors xsec_vs_energy_season2020(energy_season2020.size(), energy_season2020.data(), xsec_season2020.data(), 
                                            zeroes.data(), xsec_err_season2020.data());
    xsec_vs_energy_season2020.SetMarkerColor(kBlue);
    xsec_vs_energy_season2020.SetName("xsec_vs_energy_season2020");

    // season2021
    std::vector<double> nominal_energy_season2021 = {970, 980, 990, 1003.5};
    std::vector<double> energy_season2021 = {1003.5, 968.805, 980.248, 990.293};
    std::vector<double> xsec_season2021 = {0.0106, 0.0116, 0.013, 0.0096};
    std::vector<double> xsec_err_season2021 = {0.0007, 0.0015, 0.0011, 0.001};
    TGraphErrors xsec_vs_energy_season2021(energy_season2021.size(), energy_season2021.data(), xsec_season2021.data(), 
                                            zeroes.data(), xsec_err_season2021.data());
    xsec_vs_energy_season2021.SetMarkerColor(kMagenta);
    xsec_vs_energy_season2021.SetName("xsec_vs_energy_season2021");

    // season2022
    std::vector<double> nominal_energy_season2022 = {920, 930, 935, 937.5, 938.3, 938.9, 939.6, 940.2, 941, 942, 943.5, 945, 947.5, 948.75, 950, 951, 952, 953, 954};
    std::vector<double> energy_season2022 = {919.966, 929.985, 934.979, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 948.727, 949.995, 950.945, 952.012, 953.003, 953.997};
    std::vector<double> xsec_season2022 = {0.0029, 0.0035, 0.0032, 0.0058, 0.0043, 0.0068, 0.0077, 0.0061, 0.0075, 0.0082, 0.0094, 0.0087, 0.006, 0.0051, 0.0043, 0.0072, 0.005, 0.0036, 0.0054};
    std::vector<double> xsec_err_season2022 = {0.0005, 0.0006, 0.0005, 0.0007, 0.0005, 0.0008, 0.0008, 0.0008, 0.0009, 0.0009, 0.001, 0.0008, 0.0007, 0.0009, 0.0009, 0.0011, 0.001, 0.0008, 0.001};
    TGraphErrors xsec_vs_energy_season2022(energy_season2022.size(), energy_season2022.data(), xsec_season2022.data(), 
                                            zeroes.data(), xsec_err_season2022.data());
    xsec_vs_energy_season2022.SetMarkerColor(kBlack);
    xsec_vs_energy_season2022.SetName("xsec_vs_energy_season2022");

    xsec_vs_energy_season2019.DrawClone("AP");
    xsec_vs_energy_season2020.DrawClone("P same");
    xsec_vs_energy_season2021.DrawClone("P same");
    xsec_vs_energy_season2022.DrawClone("P same");

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("Seasons","C"); // option "C" allows to center the header
    legend->AddEntry("xsec_vs_energy_season2019","High2019","ep");
    legend->AddEntry("xsec_vs_energy_season2020","High2020","ep");
    legend->AddEntry("xsec_vs_energy_season2021","High2021","ep");
    legend->AddEntry("xsec_vs_energy_season2022","NNbar2022","ep");
    legend->DrawClone();

    canv.DrawClone();
    return 0;
}