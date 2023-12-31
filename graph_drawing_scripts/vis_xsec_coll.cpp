#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int vis_xsec_coll()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);

    // ********************* Start of Data ********************* //

    //// season2017
    std::vector<double> nominal_energy_season2017 ={}; // MeV
    std::vector<double> energy_season2017 ={}; // MeV
    std::vector<double> xsec_season2017 = {}; // nb
    std::vector<double> xsec_err_season2017 = {}; // nb


    //// season2019
    std::vector<double> nominal_energy_season2019 ={936, 945, 950, 955, 962.5, 975, 978, 987.5}; // MeV
    std::vector<double> energy_season2019 ={936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> xsec_season2019 = {0.0052, 0.0035, 0.0025, 0.2614, 0.4046, 0.4806, 0.4837, 0.5096}; // nb
    std::vector<double> xsec_err_season2019 = {0.0017, 0.0012, 0.0011, 0.0144, 0.0139, 0.011, 0.0327, 0.015}; // nb


    //// season2020
    std::vector<double> nominal_energy_season2020 ={935, 945, 950, 960, 970}; // MeV
    std::vector<double> energy_season2020 ={934.705, 945.461, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> xsec_season2020 = {0.0022, 0.0024, 0.0035, 0.3924, 0.4637}; // nb
    std::vector<double> xsec_err_season2020 = {0.0005, 0.0005, 0.0006, 0.0063, 0.0073}; // nb


    //// season2021
    std::vector<double> nominal_energy_season2021 ={1003.5, 970, 980, 990}; // MeV
    std::vector<double> energy_season2021 ={1003.5, 968.805, 980.248, 990.293}; // MeV
    std::vector<double> xsec_season2021 = {0.5299, 0.4524, 0.493, 0.5064}; // nb
    std::vector<double> xsec_err_season2021 = {0.005, 0.0091, 0.0067, 0.0071}; // nb


    //// season2022
    std::vector<double> nominal_energy_season2022 ={920, 930, 935, 937.5, 938.3, 938.9, 939.6, 940.2, 941, 942, 943.5, 945, 947.5, 948.75, 950, 951, 952, 953, 954}; // MeV
    std::vector<double> energy_season2022 ={919.966, 929.985, 934.979, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 948.727, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> xsec_season2022 = {0.0041, 0.003, 0.0038, 0.0032, 0.0032, 0.0028, 0.0029, 0.0032, 0.0033, 0.0034, 0.0032, 0.0037, 0.0025, 0.003, 0.0034, 0.0098, 0.0438, 0.0785, 0.0955}; // nb
    std::vector<double> xsec_err_season2022 = {0.0006, 0.0005, 0.0005, 0.0006, 0.0005, 0.0005, 0.0005, 0.0005, 0.0006, 0.0006, 0.0006, 0.0006, 0.0005, 0.0007, 0.0008, 0.0013, 0.0028, 0.0036, 0.0042}; // nb


    // ********************* End of Data ********************* //

    // season2019
    TGraphErrors xsec_vs_energy_season2019(energy_season2019.size(), energy_season2019.data(), xsec_season2019.data(), 
                                            zeroes.data(), xsec_err_season2019.data());
    xsec_vs_energy_season2019.SetMarkerColor(kRed);
    xsec_vs_energy_season2019.SetName("xsec_vs_energy_season2019");
    xsec_vs_energy_season2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_season2019.GetYaxis()->SetTitle("#sigma^{(vis)}_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_season2019.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} collinear events");

    // season2020
    TGraphErrors xsec_vs_energy_season2020(energy_season2020.size(), energy_season2020.data(), xsec_season2020.data(), 
                                            zeroes.data(), xsec_err_season2020.data());
    xsec_vs_energy_season2020.SetMarkerColor(kBlue);
    xsec_vs_energy_season2020.SetName("xsec_vs_energy_season2020");

    // season2021
    TGraphErrors xsec_vs_energy_season2021(energy_season2021.size(), energy_season2021.data(), xsec_season2021.data(), 
                                            zeroes.data(), xsec_err_season2021.data());
    xsec_vs_energy_season2021.SetMarkerColor(kMagenta);
    xsec_vs_energy_season2021.SetName("xsec_vs_energy_season2021");

    // season2022
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