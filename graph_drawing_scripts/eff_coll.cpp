#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int eff_coll()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // ********************* Start of Data ********************* //

    //HIGH2019
    std::vector<double> energy_HIGH2019 = {936.305, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> eff_HIGH2019 = {1, 0.0003, 0.2617, 0.341, 0.5435, 0.5285, 0.6549};
    std::vector<double> eff_err_HIGH2019 = {0, 0.0, 0.00286, 0.31128, 0.06147, 0.22349, 0.07805};

    //HIGH2020
    std::vector<double> energy_HIGH2020 = {934.705, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> eff_HIGH2020 = {1, 0.0011, 0.4582, 0.6169};
    std::vector<double> eff_err_HIGH2020 = {0, 0.0, 0.03154, 0.03941};

    //HIGH2021
    std::vector<double> energy_HIGH2021 = {968.805, 980.248, 990.293, 1003.5}; // MeV
    std::vector<double> eff_HIGH2021 = {0.6307, 0.702, 0.7156, 0.7171};
    std::vector<double> eff_err_HIGH2021 = {0.04715, 0.03504, 0.03772, 0.00043};

    //NNbar2022
    std::vector<double> energy_NNbar2022 = {919.966, 929.985, 937.505, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> eff_NNbar2022 = {1, 1, 1, 0.0001, 0.0066, 0.0128, 0.0373, 0.0612};
    std::vector<double> eff_err_NNbar2022 = {0, 0, 0, 0.0, 0.00178, 0.00088, 0.01241, 0.01379};

    // ********************* End of Data ********************* //


    //HIGH2019
    TGraphErrors eff_vs_energy_HIGH2019(energy_HIGH2019.size(), energy_HIGH2019.data(), eff_HIGH2019.data(), 
                                            zeroes.data(), eff_err_HIGH2019.data());
    eff_vs_energy_HIGH2019.SetMarkerColor(1);
    eff_vs_energy_HIGH2019.SetName("eff_vs_energy_HIGH2019");
    eff_vs_energy_HIGH2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2019.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2019.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p}collinearevents");

    //HIGH2020
    TGraphErrors eff_vs_energy_HIGH2020(energy_HIGH2020.size(), energy_HIGH2020.data(), eff_HIGH2020.data(), 
                                            zeroes.data(), eff_err_HIGH2020.data());
    eff_vs_energy_HIGH2020.SetMarkerColor(2);
    eff_vs_energy_HIGH2020.SetName("eff_vs_energy_HIGH2020");
    eff_vs_energy_HIGH2020.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2020.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2020.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p}collinearevents");

    //HIGH2021
    TGraphErrors eff_vs_energy_HIGH2021(energy_HIGH2021.size(), energy_HIGH2021.data(), eff_HIGH2021.data(), 
                                            zeroes.data(), eff_err_HIGH2021.data());
    eff_vs_energy_HIGH2021.SetMarkerColor(3);
    eff_vs_energy_HIGH2021.SetName("eff_vs_energy_HIGH2021");
    eff_vs_energy_HIGH2021.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2021.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2021.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p}collinearevents");

    //NNbar2022
    TGraphErrors eff_vs_energy_NNbar2022(energy_NNbar2022.size(), energy_NNbar2022.data(), eff_NNbar2022.data(), 
                                            zeroes.data(), eff_err_NNbar2022.data());
    eff_vs_energy_NNbar2022.SetMarkerColor(4);
    eff_vs_energy_NNbar2022.SetName("eff_vs_energy_NNbar2022");
    eff_vs_energy_NNbar2022.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_NNbar2022.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_NNbar2022.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p}collinearevents");


    eff_vs_energy_HIGH2019.DrawClone("AP");
    eff_vs_energy_HIGH2020.DrawClone("P same");
    eff_vs_energy_HIGH2021.DrawClone("P same");
    eff_vs_energy_NNbar2022.DrawClone("P same");

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("Seasons","C"); // option "C" allows to center the header

    legend->AddEntry("eff_vs_energy_HIGH2019","HIGH2019","ep");
    legend->AddEntry("eff_vs_energy_HIGH2020","HIGH2020","ep");
    legend->AddEntry("eff_vs_energy_HIGH2021","HIGH2021","ep");
    legend->AddEntry("eff_vs_energy_NNbar2022","NNbar2022","ep");
    legend->DrawClone();

    canv.DrawClone();
    return 0;
}