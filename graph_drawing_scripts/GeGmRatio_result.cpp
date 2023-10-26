#include <vector>

#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH2D.h>

int GeGmRatio_result()
{
    TCanvas canv;
    std::vector<double> zeroes(100, 0.0);
    std::vector<double> nominal_energy_season2017 = {936, 945, 950, 955, 962.5, 975, 978, 987.5};
    std::vector<double> nominal_energy_season2019 = {936, 945, 950, 955, 962.5, 975, 978, 987.5};
    std::vector<double> nominal_energy_season2020 = {935, 945, 950, 960, 970};
    std::vector<double> nominal_energy_season2021 = {970, 980, 990, 1003.5};
    std::vector<double> nominal_energy_season2022 = {920, 930, 935, 937.5, 938.3, 938.9, 939.6, 940.2, 941, 942, 943.5, 945, 947.5, 948.75, 950, 951, 952, 953, 954};

    // ********************* Start of Data ********************* //
    // HIGH2021
    std::vector<double> energy_HIGH2021 ={ 1003.5, 980.248, 990.293 }; // MeV
    std::vector<double> gegm_HIGH2021 = { 1.2971969781031716, 1.1688883607941352, 1.0491091458947444 };
    std::vector<double> gegm_err_HIGH2021 = { 0.3043517701607796, 0.3142133033466279, 0.29861346252304166 };

    // HIGH2022
    std::vector<double> energy_HIGH2022 ={ 948.727, 949.995, 950.945, 952.012, 953.003, 953.997 }; // MeV
    std::vector<double> gegm_HIGH2022 = { 0, 0, 0, 0, 0, 0 };
    std::vector<double> gegm_err_HIGH2022 = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    // HIGH2019
    std::vector<double> energy_HIGH2019 ={ 950.15, 956.084, 962.687, 972.917, 987.81 }; // MeV
    std::vector<double> gegm_HIGH2019 = { 0, 0, 0, 0.7038607816891065, 0.9762274325176485 };
    std::vector<double> gegm_err_HIGH2019 = { 0.0, 0.0, 0.0, 0.25414562754452413, 0.41097445176069036 };

    // HIGH2020
    std::vector<double> energy_HIGH2020 ={ 950.29, 960.252, 970.583 }; // MeV
    std::vector<double> gegm_HIGH2020 = { 0, 1.056603047506489, 1.0519125438932648 };
    std::vector<double> gegm_err_HIGH2020 = { 0.0, 0.33893952262903776, 0.3221645542265629 };
    // ********************* End of Data ********************* //
        
    // season2019
    TGraphErrors gegm_vs_energy_season2019(energy_HIGH2019.size(), energy_HIGH2019.data(), gegm_HIGH2019.data(), 
                                            zeroes.data(), gegm_err_HIGH2019.data());
    gegm_vs_energy_season2019.SetMarkerColor(kRed);
    gegm_vs_energy_season2019.SetName("gegm_vs_energy_season2019");

    // season2020
    TGraphErrors gegm_vs_energy_season2020(energy_HIGH2020.size(), energy_HIGH2020.data(), gegm_HIGH2020.data(), 
                                            zeroes.data(), gegm_err_HIGH2020.data());
    gegm_vs_energy_season2020.SetMarkerColor(kBlue);
    gegm_vs_energy_season2020.SetName("gegm_vs_energy_season2020");

    // season2021
    TGraphErrors gegm_vs_energy_season2021(energy_HIGH2021.size(), energy_HIGH2021.data(), gegm_HIGH2021.data(), 
                                            zeroes.data(), gegm_err_HIGH2021.data());
    gegm_vs_energy_season2021.SetMarkerColor(kMagenta);
    gegm_vs_energy_season2021.SetName("gegm_vs_energy_season2021");

    // season2022
    TGraphErrors gegm_vs_energy_season2022(energy_HIGH2022.size(), energy_HIGH2022.data(), gegm_HIGH2022.data(), 
                                            zeroes.data(), gegm_err_HIGH2022.data());
    gegm_vs_energy_season2022.SetMarkerColor(kBlack);
    gegm_vs_energy_season2022.SetName("gegm_vs_energy_season2022");
    
    auto hist = new TH2D("hist", "", 3, 910, 1010, 3, 0, 3);
    hist->GetXaxis()->SetTitle("E_{beam}, MeV");
    hist->GetYaxis()->SetTitle("|G_{e}/G_{m}|");
    hist->Draw();

    gegm_vs_energy_season2019.DrawClone("P");
    gegm_vs_energy_season2020.DrawClone("P");
    gegm_vs_energy_season2021.DrawClone("P");
    gegm_vs_energy_season2022.DrawClone("P");

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("Seasons","C"); // option "C" allows to center the header
    legend->AddEntry("gegm_vs_energy_season2019","High2019","ep");
    legend->AddEntry("gegm_vs_energy_season2020","High2020","ep");
    legend->AddEntry("gegm_vs_energy_season2021","High2021","ep");
    legend->AddEntry("gegm_vs_energy_season2022","NNbar2022","ep");
    legend->DrawClone();

    canv.DrawClone();
    return 0;
}