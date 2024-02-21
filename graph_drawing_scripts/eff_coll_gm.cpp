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
    std::vector<double> eff_HIGH2019 = {1, 0.0002, 0.1663, 0.3396, 0.4582, 0.4883, 0.5297};
    std::vector<double> eff_err_HIGH2019 = {0, 5e-05, 0.00118, 0.0015, 0.00158, 0.00158, 0.00158};

    //HIGH2020
    std::vector<double> energy_HIGH2020 = {934.705, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> eff_HIGH2020 = {1, 0.0007, 0.3536, 0.49};
    std::vector<double> eff_err_HIGH2020 = {0, 9e-05, 0.00151, 0.00158};

    //HIGH2021
    std::vector<double> energy_HIGH2021 = {968.805, 980.248, 990.293, 1003.5}; // MeV
    std::vector<double> eff_HIGH2021 = {0.4874, 0.5548, 0.5792, 0.5846};
    std::vector<double> eff_err_HIGH2021 = {0.00158, 0.00157, 0.00156, 0.00156};

    //NNbar2022
    std::vector<double> energy_NNbar2022 = {919.966, 929.985, 937.505, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> eff_NNbar2022 = {1, 1, 1, 0.0, 0.0036, 0.0128, 0.0328, 0.0612};
    std::vector<double> eff_err_NNbar2022 = {0, 0, 0, 2e-05, 0.00019, 0.00036, 0.00056, 0.00076};

    // ********************* End of Data ********************* //


    //HIGH2019
    TGraphErrors eff_vs_energy_HIGH2019(energy_HIGH2019.size(), energy_HIGH2019.data(), eff_HIGH2019.data(), 
                                            zeroes.data(), eff_err_HIGH2019.data());
    eff_vs_energy_HIGH2019.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_HIGH2019.GetYaxis()->SetLimits(-0.1, 5);
    eff_vs_energy_HIGH2019.SetMarkerColor(1);
    eff_vs_energy_HIGH2019.SetName("eff_vs_energy_HIGH2019");
    eff_vs_energy_HIGH2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2019.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2019.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p}collinearevents");

    //HIGH2020
    TGraphErrors eff_vs_energy_HIGH2020(energy_HIGH2020.size(), energy_HIGH2020.data(), eff_HIGH2020.data(), 
                                            zeroes.data(), eff_err_HIGH2020.data());
    eff_vs_energy_HIGH2020.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_HIGH2020.GetYaxis()->SetLimits(-0.1, 5);
    eff_vs_energy_HIGH2020.SetMarkerColor(2);
    eff_vs_energy_HIGH2020.SetName("eff_vs_energy_HIGH2020");
    eff_vs_energy_HIGH2020.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2020.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2020.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p}collinearevents");

    //HIGH2021
    TGraphErrors eff_vs_energy_HIGH2021(energy_HIGH2021.size(), energy_HIGH2021.data(), eff_HIGH2021.data(), 
                                            zeroes.data(), eff_err_HIGH2021.data());
    eff_vs_energy_HIGH2021.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_HIGH2021.GetYaxis()->SetLimits(-0.1, 5);
    eff_vs_energy_HIGH2021.SetMarkerColor(3);
    eff_vs_energy_HIGH2021.SetName("eff_vs_energy_HIGH2021");
    eff_vs_energy_HIGH2021.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_vs_energy_HIGH2021.GetYaxis()->SetTitle("#varepsilon, nb");
    eff_vs_energy_HIGH2021.SetTitle("Efficiency for e^{+}e^{-} #rightarrow p#bar{p}collinearevents");

    //NNbar2022
    TGraphErrors eff_vs_energy_NNbar2022(energy_NNbar2022.size(), energy_NNbar2022.data(), eff_NNbar2022.data(), 
                                            zeroes.data(), eff_err_NNbar2022.data());
    eff_vs_energy_NNbar2022.GetXaxis()->SetLimits(915, 1010);
    eff_vs_energy_NNbar2022.GetYaxis()->SetLimits(-0.1, 5);
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