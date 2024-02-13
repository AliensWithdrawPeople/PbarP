#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>

int eff_coll_ge()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    // ********************* Start of Data ********************* //
    //season2019
    std::vector<double> energy_season2019 = {936.305, 950.15, 956.084, 962.687, 972.917, 977.158, 987.81}; // MeV
    std::vector<double> ge_eff_season2019 = {0, 0.0004, 0.2626, 0.4982, 0.6629, 0.6996, 0.7488};
    std::vector<double> ge_eff_err_season2019 = {0, 0.0, 0.0006, 0.0008, 0.0007, 0.0007, 0.0006};

    //season2020
    std::vector<double> energy_season2020 = {934.705, 950.29, 960.252, 970.583}; // MeV
    std::vector<double> ge_eff_season2020 = {0, 0.0014, 0.5249, 0.7005};
    std::vector<double> ge_eff_err_season2020 = {0, 0.0, 0.0008, 0.0007};

    //season2021
    std::vector<double> energy_season2021 = {968.805, 980.248, 990.293, 1003.5}; // MeV
    std::vector<double> ge_eff_season2021 = {0.6953, 0.7773, 0.8024, 0};
    std::vector<double> ge_eff_err_season2021 = {0.0007, 0.0005, 0.0005, 0.0005};

    //season2022
    std::vector<double> energy_season2022 = {919.966, 929.985, 937.505, 949.995, 950.945, 952.012, 953.003, 953.997}; // MeV
    std::vector<double> ge_eff_season2022 = {0, 0, 0, 0.0001, 0.0075, 0.0258, 0.0626, 0.1131};
    std::vector<double> ge_eff_err_season2022 = {0, 0, 0, 0.0, 0.0, 0.0001, 0.0002, 0.0003};
    // ********************* End of Data ********************* //

    TGraphErrors eff_season2019(energy_season2019.size(), energy_season2019.data(), ge_eff_season2019.data(), zeroes.data(), ge_eff_err_season2019.data());
    TGraphErrors eff_season2020(energy_season2020.size(), energy_season2020.data(), ge_eff_season2020.data(), zeroes.data(), ge_eff_err_season2020.data());
    TGraphErrors eff_season2021(energy_season2021.size(), energy_season2021.data(), ge_eff_season2021.data(), zeroes.data(), ge_eff_err_season2021.data());
    TGraphErrors eff_season2022(energy_season2022.size(), energy_season2022.data(), ge_eff_season2022.data(), zeroes.data(), ge_eff_err_season2022.data());

    eff_season2019.SetMarkerColor(kRed);
    eff_season2019.SetName("eff_season2019");
    eff_season2019.GetXaxis()->SetTitle("E_{beam}, MeV");
    eff_season2019.GetYaxis()->SetTitle("#varepsilon_{e^{+}e^{-} #rightarrow p#bar{p}}");
    eff_season2019.SetTitle("Collinear events, |G_{E}|^{2} = 1, |G_{M}|^{2} = 0");

    eff_season2020.SetMarkerColor(kBlue);
    eff_season2020.SetName("eff_season2020");

    eff_season2021.SetMarkerColor(kMagenta);
    eff_season2021.SetName("eff_season2021");

    eff_season2022.SetMarkerColor(kBlack);
    eff_season2022.SetName("eff_season2022");

    eff_season2019.DrawClone("AP");
    eff_season2020.DrawClone("same P");
    eff_season2021.DrawClone("same P");
    eff_season2022.DrawClone("same P");

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("Seasons","C"); // option "C" allows to center the header
    legend->AddEntry("eff_season2019","High2019","ep");
    legend->AddEntry("eff_season2020","High2020","ep");
    legend->AddEntry("eff_season2021","High2021","ep");
    legend->AddEntry("eff_season2022","NNbar2022","ep");
    
    legend->DrawClone();
    canv.DrawClone();
    return 0;
}