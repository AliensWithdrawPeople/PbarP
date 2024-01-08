#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int vis_xsec_stars()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);

    // ********************* Start of Data ********************* //

    //// season2017
    std::vector<double> nominal_energy_season2017 ={930, 936, 937.4, 937.5, 938.3, 938.9, 939.6, 940.2, 940.8, 942, 950, 960, 971, 981}; // MeV
    std::vector<double> energy_season2017 ={930.481, 935.478, 937.388, 937.218, 938.176, 938.723, 939.467, 940.166, 940.608, 941.882, 950.359, 960.625, 971.253, 981.947}; // MeV
    std::vector<double> xsec_season2017 = {0.0002, 0.003, 0.0063, 0.002, 0.0122, 0.0255, 0.0354, 0.0423, 0.0535, 0.0555, 0.0325, 0.0085, 0.0026, 0.0035}; // nb
    std::vector<double> xsec_err_season2017 = {0.0019, 0.0033, 0.003, 0.0034, 0.0034, 0.0047, 0.0058, 0.0062, 0.0067, 0.0081, 0.0072, 0.0042, 0.0025, 0.003}; // nb


    //// season2019
    std::vector<double> nominal_energy_season2019 ={936, 945, 950, 955, 962.5, 975, 978, 987.5}; // MeV
    std::vector<double> energy_season2019 ={936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> xsec_season2019 = {-0.0005, 0.0674, 0.0424, 0.01, 0.0076, 0.005, -0.0007, 0.0046}; // nb
    std::vector<double> xsec_err_season2019 = {0.0018, 0.007, 0.0062, 0.0045, 0.0034, 0.0021, 0.0038, 0.0027}; // nb


    //// season2020
    std::vector<double> nominal_energy_season2020 ={935, 945, 950, 960, 970}; // MeV
    std::vector<double> energy_season2020 ={934.705, 945.461, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> xsec_season2020 = {0.0009, 0.0682, 0.0371, 0.0056, 0.0037}; // nb
    std::vector<double> xsec_err_season2020 = {0.0009, 0.0035, 0.0026, 0.0013, 0.0013}; // nb


    //// season2021
    std::vector<double> nominal_energy_season2021 ={1003.5, 970, 980, 990}; // MeV
    std::vector<double> energy_season2021 ={1003.5, 968.805, 980.248, 990.293}; // MeV
    std::vector<double> xsec_season2021 = {0.004, 0.0081, 0.0072, 0.0029}; // nb
    std::vector<double> xsec_err_season2021 = {0.0008, 0.002, 0.0014, 0.0011}; // nb


    //// season2022
    std::vector<double> nominal_energy_season2022 ={920, 930, 935, 937.5, 938.3, 938.9, 939.6, 940.2, 941, 942, 943.5, 945, 947.5, 948.75, 950, 951, 952, 953, 954}; // MeV
    std::vector<double> energy_season2022 ={919.966, 929.985, 934.979, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 948.727, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> xsec_season2022 = {-0.0001, 0.0022, 0.0012, 0.0018, 0.0154, 0.0294, 0.0432, 0.0479, 0.0491, 0.0555, 0.0577, 0.0588, 0.0616, 0.0545, 0.0344, 0.0234, 0.0216, 0.0157, 0.0125}; // nb
    std::vector<double> xsec_err_season2022 = {0.0007, 0.001, 0.0007, 0.0009, 0.0015, 0.0022, 0.0026, 0.0027, 0.0028, 0.003, 0.003, 0.0028, 0.003, 0.0036, 0.0033, 0.0028, 0.0029, 0.0024, 0.0023}; // nb


    // ********************* End of Data ********************* //

    // season2019
    TGraphErrors xsec_vs_energy_season2019(energy_season2019.size(), energy_season2019.data(), xsec_season2019.data(), 
                                            zeroes.data(), xsec_err_season2019.data());
    xsec_vs_energy_season2019.SetMarkerColor(kRed);
    xsec_vs_energy_season2019.SetName("xsec_vs_energy_season2019");
    xsec_vs_energy_season2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_season2019.GetYaxis()->SetTitle("#sigma^{(vis)}_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_season2019.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} annihilation events");

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
    legend->AddEntry("xsec_vs_energy_season2017","High2019","ep");
    legend->AddEntry("xsec_vs_energy_season2019","High2019","ep");
    legend->AddEntry("xsec_vs_energy_season2020","High2020","ep");
    legend->AddEntry("xsec_vs_energy_season2021","High2021","ep");
    legend->AddEntry("xsec_vs_energy_season2022","NNbar2022","ep");
    legend->DrawClone();

    canv.DrawClone();
    return 0;
}