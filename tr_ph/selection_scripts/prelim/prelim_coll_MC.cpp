#define prelim_coll_MC_cxx
#include "prelim_coll_MC.hpp"
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
#include <tuple>
#include <utility>
#include <cmath>

# define pi 3.14159265358979323846 

void prelim_coll_MC::Loop(std::string new_file_name)
{
   if (fChain == 0) return;

   const int min_n_hit = 5;
   const double max_chi2_r = 15.;
   const double max_chi2_z = 10.; 

   const double max_coll_pbarp_vertex_rho = 1.; // cm
   const double max_track_z = 10.; // cm

   const double min_de_dx = 6e3; 
   const double max_de_dx = 3e4;

   const double min_energy_depo_for_coll_pbarp = 200; // MeV
    // For annihilation PbarP.
   const int min_vertex_track_number = 2;
   const double max_vertex_rho = 2.5; // cm
   const double min_vertex_rho = 1.5; // cm
   const double max_track_energy_deposition = 300; // MeV

   Long64_t nentries = fChain->GetEntriesFast();
   TFile *new_file = new TFile(new_file_name.c_str(), "recreate");
   auto new_tree = new TTree("prelim", "prelim_coll_PbarP");
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
   
   std::vector<int> vtrk_vec = {};
   std::vector<std::vector<int>> vind_vec = {};
   std::vector<float> vrho_vec = {};
   new_tree->Branch("nv", &nv);
   new_tree->Branch("vtrk", &vtrk_vec);
   // [ ]: Do I need vind_vec if I only seek for one vertex with 2 tracks and I push track_ids to vectors with track info.
   // new_tree->Branch("vind", &vind_vec);
   new_tree->Branch("vrho", &vrho_vec);
   
   std::vector<int> tnhit_vec = {};
   std::vector<float> tlength_vec = {};
   std::vector<float> tphi_vec = {};
   std::vector<float> tth_vec = {};
   std::vector<float> tptot_vec = {};
   std::vector<float> tphiv_vec = {};
   std::vector<float> tthv_vec = {};
   std::vector<float> tptotv_vec = {};
   std::vector<float> trho_vec = {};
   std::vector<float> tdedx_vec = {};
   std::vector<float> tz_vec = {};
   std::vector<float> tt0_vec = {};
   std::vector<float> tant_vec = {};
   std::vector<int> tcharge_vec = {};
   std::vector<float> ten_vec = {};

   std::vector<float> tphi_MC_vec = {};
   std::vector<float> tth_MC_vec = {};
   std::vector<float> tptot_MC_vec = {};

   new_tree->Branch("nt", &nt);
   new_tree->Branch("tnhit", &tnhit_vec);
   new_tree->Branch("tlength", &tlength_vec);
   new_tree->Branch("tphi", &tphi_vec);
   new_tree->Branch("tth", &tth_vec);
   new_tree->Branch("tptot", &tptot_vec);
   new_tree->Branch("tphiv", &tphiv_vec);
   new_tree->Branch("tthv", &tthv_vec);
   new_tree->Branch("tptotv", &tptotv_vec);
   new_tree->Branch("trho", &trho_vec);
   new_tree->Branch("tdedx", &tdedx_vec);
   new_tree->Branch("tz", &tz_vec);
   new_tree->Branch("tt0", &tt0_vec);
   new_tree->Branch("tant", &tant_vec);
   new_tree->Branch("tcharge", &tcharge_vec);
   new_tree->Branch("ten", &ten_vec);

   new_tree->Branch("tphi_MC", &tphi_MC_vec);
   new_tree->Branch("tth_MC", &tth_MC_vec);
   new_tree->Branch("tptot_MC", &tptot_MC_vec);

   // [(vertex_id, pos_track_id, neg_track_id)]
   std::vector<std::tuple<int, int, int>> candidates = {};

   auto check_dedx = [&min_de_dx, &max_de_dx](double dedx, double mom) {
      return max_de_dx > dedx && dedx > min_de_dx;
   };

   auto get_rho = [](double x, double y) {
      return sqrt(x * x + y * y);
   };

   auto fill_vertex_vecs = [&](int vertex_id){
      vind_vec.push_back(std::vector(std::begin(vind[vertex_id]), std::end(vind[vertex_id])));
      vrho_vec.push_back(get_rho(vxyz[vertex_id][0], vxyz[vertex_id][1]));
   };

   auto fill_track_vecs = [&](int track_id){
      tnhit_vec.push_back(tnhit[track_id]);
      tlength_vec.push_back(tlength[track_id]);
      tphi_vec.push_back(tphi[track_id]);
      tth_vec.push_back(tth[track_id]);
      tptot_vec.push_back(tptot[track_id]);
      tphiv_vec.push_back(tphiv[track_id]);
      tthv_vec.push_back(tthv[track_id]);
      tptotv_vec.push_back(tptotv[track_id]);
      trho_vec.push_back(trho[track_id]);
      tdedx_vec.push_back(tdedx[track_id]);
      tz_vec.push_back(tz[track_id]);
      tt0_vec.push_back(tt0[track_id]);
      tant_vec.push_back(tant[track_id]);
      tcharge_vec.push_back(tcharge[track_id]);
      ten_vec.push_back(ten[track_id]);
   };

   auto clear_vecs = [&](){
      vind_vec.clear();
      vrho_vec.clear();
      tnhit_vec.clear();
      tlength_vec.clear();
      tphi_vec.clear();
      tth_vec.clear();
      tptot_vec.clear();
      tphiv_vec.clear();
      tthv_vec.clear();
      tptotv_vec.clear();
      trho_vec.clear();
      tdedx_vec.clear();
      tz_vec.clear();
      tt0_vec.clear();
      tant_vec.clear();
      tcharge_vec.clear();
      ten_vec.clear();

      candidates.clear();
      tphi_MC_vec.clear();
      tth_MC_vec.clear();
      tptot_MC_vec.clear();
   };

   auto track_goodness = [&](int track_id) {
      return tnhit[track_id] >= min_n_hit && 
            tchi2r[track_id] < max_chi2_r && tchi2z[track_id] < max_chi2_z &&
            tz[track_id] < max_track_z && 
            check_dedx(tdedx[track_id], tptot[track_id]);
   };

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if(ecaltot < min_energy_depo_for_coll_pbarp)
      { continue; }

      for(int i = 0; i < nv; i++)
      {
         if(vtrk[i] != 2 || get_rho(vxyz[i][0], vxyz[i][1]) > max_coll_pbarp_vertex_rho)
         { continue; }
                  
         auto track1 = vind[i][0];
         auto track2 = vind[i][1];
         if(track_goodness(track1) && track_goodness(track2) && tcharge[track1] * tcharge[track2] < 0)
         { candidates.push_back(tcharge[track1] > 0? std::make_tuple(i, track1, track2) : std::make_tuple(i, track2, track1)); }
      }
      if(candidates.size() == 1)
      {
         fill_vertex_vecs(std::get<0>(candidates[0]));
         fill_track_vecs(std::get<1>(candidates[0]));
         fill_track_vecs(std::get<2>(candidates[0]));
         nv = vtrk_vec.size();
         tphi_MC_vec.resize(2);
         tth_MC_vec.resize(2);
         tptot_MC_vec.resize(2);
         for(int i = 0; i < nsim; i++)
         {
            auto code = simtype[i];
            if(abs(code) != 2212)
            { continue; }
            tphi_MC_vec[code > 0? 0 : 1] = simphi[i];
            tth_MC_vec[code > 0? 0 : 1] = simtheta[i];
            tptot_MC_vec[code > 0? 0 : 1] = simmom[i];
         }
         new_tree->Fill();
      }
      clear_vecs();
   }

   new_file->Write();
   new_file->Save();
}
