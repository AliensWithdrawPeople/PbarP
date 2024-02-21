#define prelim_coll_track_efficiency_cxx
#include "prelim_coll_track_efficiency.hpp"
#include <TH2.h>
#include <TH1D.h>
#include <TF1.h>
#include <TStyle.h>
#include <TTree.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TVector3.h>
#include <TLine.h>

#include <vector>
#include <set>
#include <tuple>
#include <utility>
#include <cmath>

#define pi 3.14159265358979323846

void prelim_coll_track_efficiency::Loop(std::string new_file_name)
{
    if (fChain == 0)
        return;

    const int min_n_hit = 7;
    const double max_chi2_r = 15.;
    const double max_chi2_z = 10.;

    const double max_coll_pbarp_vertex_rho = 1.; // cm
    // For negatively charged tracks:
    const double max_track_z_neg = 4;            // cm
    // For positively charged tracks:
    const double max_track_z_pos = 6;            // cm
    const double max_track_rho = 0.8;            // cm

    const double min_de_dx = 5e3;
    const double max_de_dx = 3e4;

    const double min_energy_depo_for_coll_pbarp = 200; // MeV
                                                       // For annihilation PbarP.
    const int min_vertex_track_number = 2;
    const double max_vertex_rho = 2.5;              // cm
    const double min_vertex_rho = 1.5;              // cm
    const double max_track_energy_deposition = 300; // MeV

    const double max_delta_phi = 0.15;
    const double max_delta_theta = 0.2;

    Long64_t nentries = fChain->GetEntriesFast();
    TFile *new_file = new TFile(new_file_name.c_str(), "recreate");
    auto new_tree = new TTree("prelim", "prelim_coll_track_efficiency_PbarP");
    new_tree->Branch("evnum", &evnum);
    new_tree->Branch("ebeam", &ebeam);
    new_tree->Branch("emeas", &emeas);
    new_tree->Branch("demeas", &demeas);
    new_tree->Branch("runnum", &runnum);

    new_tree->Branch("xbeam", &xbeam);
    new_tree->Branch("ybeam", &ybeam);
    new_tree->Branch("runnum", &runnum);
    new_tree->Branch("is_coll", &is_coll);
    new_tree->Branch("is_bhabha", &is_bhabha);
    new_tree->Branch("ecaltot", &ecaltot);
    new_tree->Branch("ecalneu", &ecalneu);
    new_tree->Branch("nt", &nt);
    int beam_tracks = 0;
    float min_delta_theta = -1;
    new_tree->Branch("beam_tracks", &beam_tracks);
 
    int antiproton_candidates_number = 0;
    std::vector<int> antiproton_candidates = {};

    std::vector<int> antiproton_tnhit_vec = {};
    std::vector<float> antiproton_chi2r_vec = {};
    std::vector<float> antiproton_chi2z_vec = {};
    std::vector<float> antiproton_tlength_vec = {};
    std::vector<float> antiproton_tphi_vec = {};
    std::vector<float> antiproton_tth_vec = {};
    std::vector<float> antiproton_tptot_vec = {};
    std::vector<float> antiproton_tphiv_vec = {};
    std::vector<float> antiproton_tthv_vec = {};
    std::vector<float> antiproton_tptotv_vec = {};
    std::vector<float> antiproton_trho_vec = {};
    std::vector<float> antiproton_tdedx_vec = {};
    std::vector<float> antiproton_tz_vec = {};
    std::vector<float> antiproton_tt0_vec = {};
    std::vector<float> antiproton_tant_vec = {};
    std::vector<float> antiproton_ten_vec = {};
    std::vector<float> antiproton_min_delta_theta_vec = {};

    std::vector<int> proton_tnhit_vec = {};
    std::vector<float> proton_tlength_vec = {};
    std::vector<float> proton_chi2r_vec = {};
    std::vector<float> proton_chi2z_vec = {};
    std::vector<float> proton_tphi_vec = {};
    std::vector<float> proton_tth_vec = {};
    std::vector<float> proton_tptot_vec = {};
    std::vector<float> proton_tphiv_vec = {};
    std::vector<float> proton_tthv_vec = {};
    std::vector<float> proton_tptotv_vec = {};
    std::vector<float> proton_trho_vec = {};
    std::vector<float> proton_tdedx_vec = {};
    std::vector<float> proton_tz_vec = {};
    std::vector<float> proton_tt0_vec = {};
    std::vector<float> proton_tant_vec = {};
    std::vector<float> proton_ten_vec = {};
    
    // Connecting vectors to branches of new tree.
    {
    new_tree->Branch("antiproton_number", &antiproton_candidates_number);

    new_tree->Branch("proton_tnhit", &proton_tnhit_vec);
    new_tree->Branch("proton_tlength", &proton_tlength_vec);
    new_tree->Branch("proton_chi2r", &proton_chi2r_vec);
    new_tree->Branch("proton_chi2z", &proton_chi2z_vec);
    new_tree->Branch("proton_tphi", &proton_tphi_vec);
    new_tree->Branch("proton_tth", &proton_tth_vec);
    new_tree->Branch("proton_tptot", &proton_tptot_vec);
    new_tree->Branch("proton_tphiv", &proton_tphiv_vec);
    new_tree->Branch("proton_tthv", &proton_tthv_vec);
    new_tree->Branch("proton_tptotv", &proton_tptotv_vec);
    new_tree->Branch("proton_trho", &proton_trho_vec);
    new_tree->Branch("proton_tdedx", &proton_tdedx_vec);
    new_tree->Branch("proton_tz", &proton_tz_vec);
    new_tree->Branch("proton_tt0", &proton_tt0_vec);
    new_tree->Branch("proton_tant", &proton_tant_vec);
    new_tree->Branch("proton_ten", &proton_ten_vec);

    new_tree->Branch("antiproton_tnhit", &antiproton_tnhit_vec);
    new_tree->Branch("antiproton_chi2r", &antiproton_chi2r_vec);
    new_tree->Branch("antiproton_chi2z", &antiproton_chi2z_vec);
    new_tree->Branch("antiproton_tlength", &antiproton_tlength_vec);
    new_tree->Branch("antiproton_tphi", &antiproton_tphi_vec);
    new_tree->Branch("antiproton_tth", &antiproton_tth_vec);
    new_tree->Branch("antiproton_tptot", &antiproton_tptot_vec);
    new_tree->Branch("antiproton_tphiv", &antiproton_tphiv_vec);
    new_tree->Branch("antiproton_tthv", &antiproton_tthv_vec);
    new_tree->Branch("antiproton_tptotv", &antiproton_tptotv_vec);
    new_tree->Branch("antiproton_trho", &antiproton_trho_vec);
    new_tree->Branch("antiproton_tdedx", &antiproton_tdedx_vec);
    new_tree->Branch("antiproton_tz", &antiproton_tz_vec);
    new_tree->Branch("antiproton_tt0", &antiproton_tt0_vec);
    new_tree->Branch("antiproton_tant", &antiproton_tant_vec);
    new_tree->Branch("antiproton_ten", &antiproton_ten_vec);
    new_tree->Branch("antiproton_min_delta_theta", &antiproton_min_delta_theta_vec);
    }
    
    // [(neg_track_id, pos_track_id)]

    auto check_dedx = [&min_de_dx, &max_de_dx, this](double dedx, double mom)
    { 
        return  max_de_dx > dedx && 
                // dedx > 3800 && mom > 70; // For MC
                dedx > min_de_dx &&
                (this->emeas > 985? dedx > 1.38906e6/(mom - 41.1525) + 1500 : dedx > 1.38906e6/(mom - 41.1525) + 2106.22); 
    };

    auto is_collinear = [&](int track1, int track2)
    {
        TVector3 vec1(1, 1, 1);
        TVector3 vec2(1, 1, 1);
        vec1.SetMagThetaPhi(1, tth[track1], tphi[track1]);
        vec2.SetMagThetaPhi(1, tth[track2], tphi[track2]);
        auto delta_phi = fabs(fabs(tphi[track1] - tphi[track2]) - pi);
        auto delta_theta = fabs(tth[track1] + tth[track2] - pi);
        return (delta_phi < max_delta_phi) && (delta_theta < max_delta_theta) && vec1.Dot(vec2) < 0;
    };

    auto delta_theta = [&](int track1, int track2)
    { return fabs(tth[track1] + tth[track2] - pi); };

    auto is_full_collinear = [&](int track1, int track2, float cut = 1)
    {
        TVector3 vec1(1, 1, 1);
        TVector3 vec2(1, 1, 1);
        vec1.SetMagThetaPhi(1, tth[track1], tphi[track1]);
        vec2.SetMagThetaPhi(1, tth[track2], tphi[track2]);
        return fabs(vec1.Angle(vec2)) < 1;
    };

    auto fill_proton_track_vecs = [&](int track_id)
    {
        proton_tnhit_vec.push_back(tnhit[track_id]);
        proton_tlength_vec.push_back(tlength[track_id]);
        proton_chi2r_vec.push_back(tchi2r[track_id]);
        proton_chi2z_vec.push_back(tchi2z[track_id]);
        proton_tphi_vec.push_back(tphi[track_id]);
        proton_tth_vec.push_back(tth[track_id]);
        proton_tptot_vec.push_back(tptot[track_id]);
        proton_tphiv_vec.push_back(tphiv[track_id]);
        proton_tthv_vec.push_back(tthv[track_id]);
        proton_tptotv_vec.push_back(tptotv[track_id]);
        proton_trho_vec.push_back(trho[track_id]);
        proton_tdedx_vec.push_back(tdedx[track_id]);
        proton_tz_vec.push_back(tz[track_id]);
        proton_tt0_vec.push_back(tt0[track_id]);
        proton_tant_vec.push_back(tant[track_id]);
        proton_ten_vec.push_back(ten[track_id]);
    };

    auto fill_antiproton_track_vecs = [&](int track_id)
    {
        antiproton_tnhit_vec.push_back(tnhit[track_id]);
        antiproton_tlength_vec.push_back(tlength[track_id]);
        antiproton_chi2r_vec.push_back(tchi2r[track_id]);
        antiproton_chi2z_vec.push_back(tchi2z[track_id]);
        antiproton_tphi_vec.push_back(tphi[track_id]);
        antiproton_tth_vec.push_back(tth[track_id]);
        antiproton_tptot_vec.push_back(tptot[track_id]);
        antiproton_tphiv_vec.push_back(tphiv[track_id]);
        antiproton_tthv_vec.push_back(tthv[track_id]);
        antiproton_tptotv_vec.push_back(tptotv[track_id]);
        antiproton_trho_vec.push_back(trho[track_id]);
        antiproton_tdedx_vec.push_back(tdedx[track_id]);
        antiproton_tz_vec.push_back(tz[track_id]);
        antiproton_tt0_vec.push_back(tt0[track_id]);
        antiproton_tant_vec.push_back(tant[track_id]);
        antiproton_ten_vec.push_back(ten[track_id]);
        antiproton_min_delta_theta_vec.push_back(min_delta_theta);
    };

    auto clear_vecs = [&]()
    {
        proton_tnhit_vec.clear();
        proton_tlength_vec.clear();
        proton_chi2r_vec.clear();
        proton_chi2z_vec.clear();
        proton_tphi_vec.clear();
        proton_tth_vec.clear();
        proton_tptot_vec.clear();
        proton_tphiv_vec.clear();
        proton_tthv_vec.clear();
        proton_tptotv_vec.clear();
        proton_trho_vec.clear();
        proton_tdedx_vec.clear();
        proton_tz_vec.clear();
        proton_tt0_vec.clear();
        proton_tant_vec.clear();
        proton_ten_vec.clear();

        antiproton_tnhit_vec.clear();
        antiproton_tlength_vec.clear();
        antiproton_chi2r_vec.clear();
        antiproton_chi2z_vec.clear();
        antiproton_tphi_vec.clear();
        antiproton_tth_vec.clear();
        antiproton_tptot_vec.clear();
        antiproton_tphiv_vec.clear();
        antiproton_tthv_vec.clear();
        antiproton_tptotv_vec.clear();
        antiproton_trho_vec.clear();
        antiproton_tdedx_vec.clear();
        antiproton_tz_vec.clear();
        antiproton_tt0_vec.clear();
        antiproton_tant_vec.clear();
        antiproton_ten_vec.clear();
        antiproton_min_delta_theta_vec.clear();
    };

    auto clear_everything = [&]()
    {
        antiproton_candidates.clear();
        clear_vecs();
        antiproton_candidates_number = 0;
        beam_tracks = 0;
        min_delta_theta = -1;
    };

    auto track_goodness = [&](int track_id)
    {
        auto nominal_avg_momentum = sqrt(emeas * emeas - 938.272 * 938.272);
        return tnhit[track_id] >= min_n_hit &&
               tchi2r[track_id] < max_chi2_r && 
               tchi2z[track_id] < max_chi2_z &&
               fabs(tz[track_id]) < (tcharge[track_id] < 0? max_track_z_neg : max_track_z_pos) &&
               fabs(trho[track_id]) < max_track_rho &&
               check_dedx(tdedx[track_id], tptot[track_id]) &&
               fabs(tptot[track_id] - nominal_avg_momentum) < 100;
    };

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0)
            break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;

        if (ecaltot < min_energy_depo_for_coll_pbarp)
        { continue; }
        for (int i = 0; i < nt; i++)
        {
            if(fabs(trho[i]) < 3)
            { beam_tracks++; }

            if (track_goodness(i) && tcharge[i] < 0)
            { antiproton_candidates.push_back(i); }
        }

        if(antiproton_candidates.size() == 0)
        {
            clear_everything();
            continue;
        }

        antiproton_candidates_number = antiproton_candidates.size();
        std::set<int> proton_candidates = {};
        bool break_flag = false;
        for(const auto& antiproton_candidate_track :  antiproton_candidates)
        {
            for (int i = 0; i < nt; i++)
            {          
                if(antiproton_candidate_track == i)
                { continue; }
                if(auto dTheta = delta_theta(antiproton_candidate_track, i); ((min_delta_theta > 0)? dTheta < min_delta_theta : true) && is_full_collinear(antiproton_candidate_track, i, 2.5))
                { min_delta_theta = dTheta; }
                
                if (is_full_collinear(antiproton_candidate_track, i))
                { 
                    break_flag = true;
                    break;
                }

                if (antiproton_candidate_track != i && track_goodness(i) && tcharge[i] > 0 && is_collinear(antiproton_candidate_track, i))
                { proton_candidates.insert(i); }
            }
            fill_antiproton_track_vecs(antiproton_candidate_track);

            if(break_flag)
            { break; }
        }
        if(break_flag)
        {
            clear_everything();
            proton_candidates.clear();
            break_flag = false;
            continue;
        }

        for(const auto& proton_candidate :  proton_candidates)
        { fill_proton_track_vecs(proton_candidate); }

        new_tree->Fill();
        proton_candidates.clear();
        clear_everything();
        break_flag = false;
    }

    new_file->Write();
    new_file->Save();
}
