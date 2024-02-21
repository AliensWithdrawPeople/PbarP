#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int eff_stars_Ge()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // ********************* Start of Data ********************* //

    //HIGH2017
    std::vector<double> energy_HIGH2017 = {930.481, 935.478, 938.176, 938.723, 939.467, 940.166, 940.608, 941.882, 950.359, 960.625, 971.253, 981.947}; // MeV
    std::vector<double> eff_HIGH2017 = {1, 1, 1, 0.1741, 0.1817, 0.1746, 0.1838, 0.1811, 0.0677, 0.0076, 0.004, 0.0027};
    std::vector<double> eff_err_HIGH2017 = {0, 0, 0, 0.0012, 0.00122, 0.0012, 0.00122, 0.00122, 0.00079, 0.00027, 0.0002, 0.00016};

    //HIGH2019
    std::vector<double> energy_HIGH2019 = {936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> eff_HIGH2019 = {1, 0.1959, 0.0792, 0.0138, 0.0069, 0.0039, 0.0032, 0.0029};
    std::vector<double> eff_err_HIGH2019 = {0, 0.00126, 0.00085, 0.00037, 0.00026, 0.0002, 0.00018, 0.00017};

    //HIGH2020
    std::vector<double> energy_HIGH2020 = {934.705, 945.461, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> eff_HIGH2020 = {1, 0.1907, 0.0774, 0.0077, 0.004};
    std::vector<double> eff_err_HIGH2020 = {0, 0.00124, 0.00085, 0.00028, 0.0002};

    //HIGH2021
    std::vector<double> energy_HIGH2021 = {968.805, 980.248, 990.293, 1003.5}; // MeV
    std::vector<double> eff_HIGH2021 = {0.0044, 0.0026, 0.0025, 0.0019};
    std::vector<double> eff_err_HIGH2021 = {0.00021, 0.00016, 0.00016, 0.00014};

    //NNbar2022
    std::vector<double> energy_NNbar2022 = {919.966, 929.985, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> eff_NNbar2022 = {1, 1, 1, 0.0824, 0.1809, 0.1828, 0.1857, 0.1829, 0.1839, 0.1863, 0.1757, 0.1727, 0.0862, 0.0527, 0.0336, 0.0235, 0.0177};
    std::vector<double> eff_err_NNbar2022 = {0, 0, 0, 0.00265, 0.00122, 0.00122, 0.00123, 0.00122, 0.00122, 0.00123, 0.0012, 0.0012, 0.00089, 0.00071, 0.00057, 0.00048, 0.00042};

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
    eff_vs_energy_HIGH2017.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events for G_{M} = 0, G_{E} = 1");

    //HIGH2019
    TGraphErrors eff_vs_energy_HIGH2019(energy_HIGH2019.size(), energy_HIGH2019.data(), eff_HIGH2019.data(), 
                                            zeroes.data(), eff_err_HIGH2019.data());
    eff_vs_energy_HIGH2019.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_HIGH2019.GetYaxis()->SetLimits(-0.1, 5);
    eff_vs_energy_HIGH2019.SetMarkerColor(2);
    eff_vs_energy_HIGH2019.SetName("eff_vs_energy_HIGH2019");
    eff_vs_energy_HIGH2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2019.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2019.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events for G_{M} = 0, G_{E} = 1");

    //HIGH2020
    TGraphErrors eff_vs_energy_HIGH2020(energy_HIGH2020.size(), energy_HIGH2020.data(), eff_HIGH2020.data(), 
                                            zeroes.data(), eff_err_HIGH2020.data());
    eff_vs_energy_HIGH2020.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_HIGH2020.GetYaxis()->SetLimits(-0.1, 5);
    eff_vs_energy_HIGH2020.SetMarkerColor(3);
    eff_vs_energy_HIGH2020.SetName("eff_vs_energy_HIGH2020");
    eff_vs_energy_HIGH2020.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2020.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2020.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events for G_{M} = 0, G_{E} = 1");

    //HIGH2021
    TGraphErrors eff_vs_energy_HIGH2021(energy_HIGH2021.size(), energy_HIGH2021.data(), eff_HIGH2021.data(), 
                                            zeroes.data(), eff_err_HIGH2021.data());
    eff_vs_energy_HIGH2021.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_HIGH2021.GetYaxis()->SetLimits(-0.1, 5);
    eff_vs_energy_HIGH2021.SetMarkerColor(4);
    eff_vs_energy_HIGH2021.SetName("eff_vs_energy_HIGH2021");
    eff_vs_energy_HIGH2021.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2021.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2021.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events for G_{M} = 0, G_{E} = 1");

    //NNbar2022
    TGraphErrors eff_vs_energy_NNbar2022(energy_NNbar2022.size(), energy_NNbar2022.data(), eff_NNbar2022.data(), 
                                            zeroes.data(), eff_err_NNbar2022.data());
    eff_vs_energy_NNbar2022.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_NNbar2022.GetYaxis()->SetLimits(-0.1, 5);
    eff_vs_energy_NNbar2022.SetMarkerColor(45);
    eff_vs_energy_NNbar2022.SetName("eff_vs_energy_NNbar2022");
    eff_vs_energy_NNbar2022.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_NNbar2022.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_NNbar2022.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events for G_{M} = 0, G_{E} = 1");


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