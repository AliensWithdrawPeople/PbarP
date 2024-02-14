#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int xsec_stars()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // ********************* Start of Data ********************* //

    //HIGH2017
    std::vector<double> energy_HIGH2017 = {930.481, 935.478, 938.176, 938.723, 939.467, 940.166, 940.608, 941.882, 950.359, 960.625, 971.253, 981.947}; // MeV
    std::vector<double> xsec_HIGH2017 = {-0.0003, 0.0014, 0.0119, 0.3265, 0.4983, 0.5758, 0.6338, 0.6538, 1.1794, 1.885, 2.2408, 5.1112}; // nb
    std::vector<double> xsec_err_HIGH2017 = {0.0027, 0.0033, 0.004, 0.073, 0.0878, 0.0953, 0.1001, 0.1182, 0.3073, 3.367, 8.174, 27.8632}; // nb

    //HIGH2019
    std::vector<double> energy_HIGH2019 = {936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> xsec_HIGH2019 = {0.0013, 0.8492, 1.0521, 1.6884, 2.9021, 1.9619, 2.8133, 1.056}; // nb
    std::vector<double> xsec_err_HIGH2019 = {0.0027, 0.1075, 0.2376, 1.9951, 6.4916, 7.02, 12.2954, 5.9428}; // nb

    //HIGH2020
    std::vector<double> energy_HIGH2020 = {934.705, 945.461, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> xsec_HIGH2020 = {0.0027, 0.8199, 0.9578, 1.718, 3.2175}; // nb
    std::vector<double> xsec_err_HIGH2020 = {0.0013, 0.0789, 0.1715, 2.7568, 11.0172}; // nb

    //HIGH2021
    std::vector<double> energy_HIGH2021 = {968.805, 980.248, 990.293, 1003.5}; // MeV
    std::vector<double> xsec_HIGH2021 = {4.3079, 5.9388, 3.8302, 4.2016}; // nb
    std::vector<double> xsec_err_HIGH2021 = {13.8809, 30.1391, 22.3593, 32.5346}; // nb

    //NNbar2022
    std::vector<double> energy_NNbar2022 = {919.966, 929.985, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> xsec_NNbar2022 = {0.0006, 0.0032, 0.0028, 0.1918, 0.4078, 0.5306, 0.5707, 0.607, 0.6824, 0.7016, 0.7343, 0.8503, 0.8467, 0.8885, 0.8399, 0.882, 0.706}; // nb
    std::vector<double> xsec_err_NNbar2022 = {0.0011, 0.0013, 0.0012, 0.0215, 0.0476, 0.0568, 0.0587, 0.0632, 0.0689, 0.0695, 0.0739, 0.0851, 0.1545, 0.7527, 0.2298, 0.5114, 0.379}; // nb

    // ********************* End of Data ********************* //


    //HIGH2017
    TGraphErrors xsec_vs_energy_HIGH2017(energy_HIGH2017.size(), energy_HIGH2017.data(), xsec_HIGH2017.data(), 
                                            zeroes.data(), xsec_err_HIGH2017.data());
    xsec_vs_energy_HIGH2017.SetMarkerColor(1);
    xsec_vs_energy_HIGH2017.SetName("xsec_vs_energy_HIGH2017");
    xsec_vs_energy_HIGH2017.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_HIGH2017.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_HIGH2017.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} annihilation events");

    //HIGH2019
    TGraphErrors xsec_vs_energy_HIGH2019(energy_HIGH2019.size(), energy_HIGH2019.data(), xsec_HIGH2019.data(), 
                                            zeroes.data(), xsec_err_HIGH2019.data());
    xsec_vs_energy_HIGH2019.SetMarkerColor(2);
    xsec_vs_energy_HIGH2019.SetName("xsec_vs_energy_HIGH2019");
    xsec_vs_energy_HIGH2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_HIGH2019.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_HIGH2019.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} annihilation events");

    //HIGH2020
    TGraphErrors xsec_vs_energy_HIGH2020(energy_HIGH2020.size(), energy_HIGH2020.data(), xsec_HIGH2020.data(), 
                                            zeroes.data(), xsec_err_HIGH2020.data());
    xsec_vs_energy_HIGH2020.SetMarkerColor(3);
    xsec_vs_energy_HIGH2020.SetName("xsec_vs_energy_HIGH2020");
    xsec_vs_energy_HIGH2020.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_HIGH2020.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_HIGH2020.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} annihilation events");

    //HIGH2021
    TGraphErrors xsec_vs_energy_HIGH2021(energy_HIGH2021.size(), energy_HIGH2021.data(), xsec_HIGH2021.data(), 
                                            zeroes.data(), xsec_err_HIGH2021.data());
    xsec_vs_energy_HIGH2021.SetMarkerColor(4);
    xsec_vs_energy_HIGH2021.SetName("xsec_vs_energy_HIGH2021");
    xsec_vs_energy_HIGH2021.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_HIGH2021.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_HIGH2021.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} annihilation events");

    //NNbar2022
    TGraphErrors xsec_vs_energy_NNbar2022(energy_NNbar2022.size(), energy_NNbar2022.data(), xsec_NNbar2022.data(), 
                                            zeroes.data(), xsec_err_NNbar2022.data());
    xsec_vs_energy_NNbar2022.SetMarkerColor(45);
    xsec_vs_energy_NNbar2022.SetName("xsec_vs_energy_NNbar2022");
    xsec_vs_energy_NNbar2022.GetXaxis()->SetTitle("E_{beam}, MeV");
    xsec_vs_energy_NNbar2022.GetYaxis()->SetTitle("#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb");
    xsec_vs_energy_NNbar2022.SetTitle("e^{+}e^{-} #rightarrow p#bar{p} annihilation events");


    xsec_vs_energy_HIGH2017.DrawClone("AP");
    xsec_vs_energy_HIGH2019.DrawClone("P same");
    xsec_vs_energy_HIGH2020.DrawClone("P same");
    xsec_vs_energy_HIGH2021.DrawClone("P same");
    xsec_vs_energy_NNbar2022.DrawClone("P same");

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("Seasons","C"); // option "C" allows to center the header

    legend->AddEntry("xsec_vs_energy_HIGH2017","HIGH2017","ep");
    legend->AddEntry("xsec_vs_energy_HIGH2019","HIGH2019","ep");
    legend->AddEntry("xsec_vs_energy_HIGH2020","HIGH2020","ep");
    legend->AddEntry("xsec_vs_energy_HIGH2021","HIGH2021","ep");
    legend->AddEntry("xsec_vs_energy_NNbar2022","NNbar2022","ep");
    legend->DrawClone();

    canv.DrawClone();
    return 0;
}