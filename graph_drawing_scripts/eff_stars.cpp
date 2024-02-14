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

    //HIGH2017
    std::vector<double> energy_HIGH2017 = {930.481, 935.478, 938.176, 938.723, 939.467, 940.166, 940.608, 941.882, 950.359, 960.625, 971.253, 981.947}; // MeV
    std::vector<double> eff_HIGH2017 = {1, 1, 1, 0.0766, 0.0811, 0.0785, 0.0828, 0.0817, 0.037, 0.0042, 0.002, 0.0013};
    std::vector<double> eff_err_HIGH2017 = {0, 0, 0, 0.00701, 0.00701, 0.00701, 0.00701, 0.00701, 0.007, 0.007, 0.007, 0.007};

    //HIGH2019
    std::vector<double> energy_HIGH2019 = {936.305, 944.817, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> eff_HIGH2019 = {1, 0.089, 0.0431, 0.0065, 0.0041, 0.002, 0.0017, 0.0013};
    std::vector<double> eff_err_HIGH2019 = {0, 0.00701, 0.007, 0.00701, 0.00914, 0.00702, 0.00712, 0.00701};

    //HIGH2020
    std::vector<double> energy_HIGH2020 = {934.705, 945.461, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> eff_HIGH2020 = {1, 0.0866, 0.0426, 0.0044, 0.0021};
    std::vector<double> eff_err_HIGH2020 = {0, 0.00701, 0.007, 0.00704, 0.00701};

    //HIGH2021
    std::vector<double> energy_HIGH2021 = {968.805, 980.248, 990.293, 1003.5}; // MeV
    std::vector<double> eff_HIGH2021 = {0.0022, 0.0014, 0.0012, 0.0009};
    std::vector<double> eff_err_HIGH2021 = {0.00701, 0.007, 0.007, 0.007};

    //NNbar2022
    std::vector<double> energy_NNbar2022 = {919.966, 929.985, 937.505, 938.323, 938.887, 939.594, 940.207, 940.96, 941.995, 943.495, 944.993, 947.5, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> eff_NNbar2022 = {1, 1, 1, 0.0824, 0.0797, 0.082, 0.0841, 0.0824, 0.0835, 0.0844, 0.0806, 0.0789, 0.0456, 0.0282, 0.0305, 0.021, 0.017};
    std::vector<double> eff_err_NNbar2022 = {0, 0, 0, 0.00265, 0.00701, 0.00701, 0.00701, 0.00701, 0.00701, 0.00701, 0.00701, 0.00701, 0.007, 0.02366, 0.00736, 0.01174, 0.00822};

    // ********************* End of Data ********************* //


    //HIGH2017
    TGraphErrors eff_vs_energy_HIGH2017(energy_HIGH2017.size(), energy_HIGH2017.data(), eff_HIGH2017.data(), 
                                            zeroes.data(), eff_err_HIGH2017.data());
    eff_vs_energy_HIGH2017.SetMarkerColor(1);
    eff_vs_energy_HIGH2017.SetName("eff_vs_energy_HIGH2017");
    eff_vs_energy_HIGH2017.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2017.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2017.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events");

    //HIGH2019
    TGraphErrors eff_vs_energy_HIGH2019(energy_HIGH2019.size(), energy_HIGH2019.data(), eff_HIGH2019.data(), 
                                            zeroes.data(), eff_err_HIGH2019.data());
    eff_vs_energy_HIGH2019.SetMarkerColor(2);
    eff_vs_energy_HIGH2019.SetName("eff_vs_energy_HIGH2019");
    eff_vs_energy_HIGH2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2019.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2019.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events");

    //HIGH2020
    TGraphErrors eff_vs_energy_HIGH2020(energy_HIGH2020.size(), energy_HIGH2020.data(), eff_HIGH2020.data(), 
                                            zeroes.data(), eff_err_HIGH2020.data());
    eff_vs_energy_HIGH2020.SetMarkerColor(3);
    eff_vs_energy_HIGH2020.SetName("eff_vs_energy_HIGH2020");
    eff_vs_energy_HIGH2020.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2020.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2020.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events");

    //HIGH2021
    TGraphErrors eff_vs_energy_HIGH2021(energy_HIGH2021.size(), energy_HIGH2021.data(), eff_HIGH2021.data(), 
                                            zeroes.data(), eff_err_HIGH2021.data());
    eff_vs_energy_HIGH2021.SetMarkerColor(4);
    eff_vs_energy_HIGH2021.SetName("eff_vs_energy_HIGH2021");
    eff_vs_energy_HIGH2021.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2021.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2021.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events");

    //NNbar2022
    TGraphErrors eff_vs_energy_NNbar2022(energy_NNbar2022.size(), energy_NNbar2022.data(), eff_NNbar2022.data(), 
                                            zeroes.data(), eff_err_NNbar2022.data());
    eff_vs_energy_NNbar2022.SetMarkerColor(45);
    eff_vs_energy_NNbar2022.SetName("eff_vs_energy_NNbar2022");
    eff_vs_energy_NNbar2022.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_NNbar2022.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_NNbar2022.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p} annihilation events");


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