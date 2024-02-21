#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int eff_stars_Gm()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // ********************* Start of Data ********************* //

    //HIGH2017
    std::vector<double> energy_HIGH2017 = {930.481, 935.478, 938.176, 938.723, 939.467, 940.166, 940.608, 941.882, 950.359, 960.625, 971.253, 981.947}; // MeV
    std::vector<double> eff_HIGH2017 = {1, 1, 1, 0.152, 0.1647, 0.1613, 0.1708, 0.1688, 0.0969, 0.0111, 0.0046, 0.003};
    std::vector<double> eff_err_HIGH2017 = {0, 0, 0, 0.00114, 0.00117, 0.00116, 0.00119, 0.00118, 0.00094, 0.00033, 0.00021, 0.00017};

    //HIGH2019
    std::vector<double> energy_HIGH2019 = {936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> eff_HIGH2019 = {1, 0.1861, 0.1123, 0.0273, 0.0089, 0.0045, 0.0038, 0.0028};
    std::vector<double> eff_err_HIGH2019 = {0, 0.00123, 0.001, 0.00052, 0.0003, 0.00021, 0.00019, 0.00017};

    //HIGH2020
    std::vector<double> energy_HIGH2020 = {934.705, 945.461, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> eff_HIGH2020 = {1, 0.1808, 0.1125, 0.0123, 0.0051};
    std::vector<double> eff_err_HIGH2020 = {0, 0.00122, 0.001, 0.00035, 0.00023};

    //HIGH2021
    std::vector<double> energy_HIGH2021 = {968.805, 980.248, 990.293, 1003.5}; // MeV
    std::vector<double> eff_HIGH2021 = {0.0053, 0.0037, 0.0028, 0.002};
    std::vector<double> eff_err_HIGH2021 = {0.00023, 0.00019, 0.00017, 0.00014};

    //NNbar2022
    std::vector<double> energy_NNbar2022 = {919.966, 929.985, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> eff_NNbar2022 = {1, 1, 1, 0.0824, 0.1586, 0.1679, 0.1749, 0.1697, 0.1745, 0.1754, 0.1709, 0.1662, 0.1157, 0.0881, 0.0657, 0.049, 0.0366};
    std::vector<double> eff_err_NNbar2022 = {0, 0, 0, 0.00265, 0.00116, 0.00118, 0.0012, 0.00119, 0.0012, 0.0012, 0.00119, 0.00118, 0.00101, 0.0009, 0.00078, 0.00068, 0.00059};

    // ********************* End of Data ********************* //


    //HIGH2017
    TGraphErrors eff_vs_energy_HIGH2017(energy_HIGH2017.size(), energy_HIGH2017.data(), eff_HIGH2017.data(), 
                                            zeroes.data(), eff_err_HIGH2017.data());
    eff_vs_energy_HIGH2017.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_HIGH2017.GetYaxis()->SetLimits(-0.1, 5);
    eff_vs_energy_HIGH2017.SetMarkerColor(1);
    eff_vs_energy_HIGH2017.SetName("eff_vs_energy_HIGH2017");
    eff_vs_energy_HIGH2017.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2017.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2017.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events for G_{M} = 1, G_{E} = 0");

    //HIGH2019
    TGraphErrors eff_vs_energy_HIGH2019(energy_HIGH2019.size(), energy_HIGH2019.data(), eff_HIGH2019.data(), 
                                            zeroes.data(), eff_err_HIGH2019.data());
    eff_vs_energy_HIGH2019.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_HIGH2019.GetYaxis()->SetLimits(-0.1, 5);
    eff_vs_energy_HIGH2019.SetMarkerColor(2);
    eff_vs_energy_HIGH2019.SetName("eff_vs_energy_HIGH2019");
    eff_vs_energy_HIGH2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2019.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2019.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events for G_{M} = 1, G_{E} = 0");

    //HIGH2020
    TGraphErrors eff_vs_energy_HIGH2020(energy_HIGH2020.size(), energy_HIGH2020.data(), eff_HIGH2020.data(), 
                                            zeroes.data(), eff_err_HIGH2020.data());
    eff_vs_energy_HIGH2020.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_HIGH2020.GetYaxis()->SetLimits(-0.1, 5);
    eff_vs_energy_HIGH2020.SetMarkerColor(3);
    eff_vs_energy_HIGH2020.SetName("eff_vs_energy_HIGH2020");
    eff_vs_energy_HIGH2020.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2020.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2020.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events for G_{M} = 1, G_{E} = 0");

    //HIGH2021
    TGraphErrors eff_vs_energy_HIGH2021(energy_HIGH2021.size(), energy_HIGH2021.data(), eff_HIGH2021.data(), 
                                            zeroes.data(), eff_err_HIGH2021.data());
    eff_vs_energy_HIGH2021.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_HIGH2021.GetYaxis()->SetLimits(-0.1, 5);
    eff_vs_energy_HIGH2021.SetMarkerColor(4);
    eff_vs_energy_HIGH2021.SetName("eff_vs_energy_HIGH2021");
    eff_vs_energy_HIGH2021.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2021.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2021.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events for G_{M} = 1, G_{E} = 0");

    //NNbar2022
    TGraphErrors eff_vs_energy_NNbar2022(energy_NNbar2022.size(), energy_NNbar2022.data(), eff_NNbar2022.data(), 
                                            zeroes.data(), eff_err_NNbar2022.data());
    eff_vs_energy_NNbar2022.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_NNbar2022.GetYaxis()->SetLimits(-0.1, 5);
    eff_vs_energy_NNbar2022.SetMarkerColor(45);
    eff_vs_energy_NNbar2022.SetName("eff_vs_energy_NNbar2022");
    eff_vs_energy_NNbar2022.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_NNbar2022.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_NNbar2022.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events for G_{M} = 1, G_{E} = 0");


    eff_vs_energy_HIGH2017.DrawClone("AP");
    eff_vs_energy_HIGH2019.DrawClone("P same");
    eff_vs_energy_HIGH2020.DrawClone("P same");
    eff_vs_energy_HIGH2021.DrawClone("P same");
    eff_vs_energy_NNbar2022.DrawClone("P same");

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("Seasons","C"); // option "C" allows to center the header

    legend->AddEntry("eff_vs_energy_HIGH2017","HIGH2017","ep");
    legend->AddEntry("eff_vs_energy_HIGH2019","HIGH2019","ep");
    legend->AddEntry("eff_vs_energy_HIGH2020","HIGH2020","ep");
    legend->AddEntry("eff_vs_energy_HIGH2021","HIGH2021","ep");
    legend->AddEntry("eff_vs_energy_NNbar2022","NNbar2022","ep");
    legend->DrawClone();

    canv.DrawClone();
    return 0;
}