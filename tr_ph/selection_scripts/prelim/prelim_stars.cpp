#define prelim_stars_cxx
#include "prelim_stars.hpp"
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
#include <algorithm>

# define pi 3.14159265358979323846 

void prelim_stars::Loop(std::string new_file_name)
{
   if (fChain == 0) return;

   const int min_n_hit = 5;
   const double max_chi2_r = 15.;
   const double max_chi2_z = 10.; 

   const double max_coll_pbarp_vertex_rho = 1.; // cm
   const double max_track_z = 10.; // cm

   const double min_de_dx = 6e3; 
   const double max_de_dx = 3e4;

   // For annihilation PbarP.
   const int min_vertex_track_number = 3;
   const double max_vertex_rho = 3; // cm
   const double min_vertex_rho = 0.7; // cm
   const double max_track_energy_deposition = 400; // MeV
   const double pipe_rho = 2.; // cm

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
   std::vector<bool> is_fake_vertex_vec = {};
   new_tree->Branch("nv", &nv);
   new_tree->Branch("vtrk", &vtrk_vec);
   // [ ]: Do I need vind_vec if I only seek for one vertex with 2 tracks and I push track_ids to vectors with track info.
   // new_tree->Branch("vind", &vind_vec);
   new_tree->Branch("vrho", &vrho_vec);
   new_tree->Branch("is_fake_vertex", &is_fake_vertex_vec);
   
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

   int candidates_num = 0;
   new_tree->Branch("candidates_num", &candidates_num);

   // [(vertex_id, [track_ids])]
   std::vector<std::pair<int, std::vector<int>>> candidates = {};

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
      is_fake_vertex_vec.clear();

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
   };

   auto track_goodness = [&](int track_id) {
      return tnhit[track_id] >= min_n_hit && 
            tchi2r[track_id] < max_chi2_r && tchi2z[track_id] < max_chi2_z &&
            tz[track_id] < max_track_z && 
            check_dedx(tdedx[track_id], tptot[track_id]);
   };

   auto is_proton = [&](int track_id) {
      return check_dedx(tdedx[track_id], tptot[track_id]);
   };

   bool skip = false;
   bool fake_vertex = false;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      for(int i = 0; i < nt; i++)
      {
         if(ten[i] > max_track_energy_deposition)
         {
            skip = true;
            break;
         }
      }
      
      for (int i = 0; i < nv && !skip; i++)
      {
         auto vertex_rho = get_rho(vxyz[i][0], vxyz[i][1]);
         if(max_vertex_rho > vertex_rho && vertex_rho > min_vertex_rho && vtrk[i] >= min_vertex_track_number)
         {
            std::vector<int> track_ids = {};
            track_ids.reserve(vtrk[i]);
            for(int j = 0; j < vtrk[i]; j++)
            { 
               track_ids.push_back(vind[i][j]);
               if(is_proton(track_ids.back()))
               { fake_vertex = true; }
            }
            is_fake_vertex_vec.push_back(fake_vertex);
            fake_vertex = false;
            candidates.push_back(std::make_pair(i, track_ids));
         }
      }
      
      if(!skip && candidates.size() > 0)
      {
         candidates_num = candidates.size();
         auto it_min = candidates.begin();
         if(candidates_num > 1)
         { 
            auto closest_to_pipe_vertex = [&get_rho, this, &pipe_rho](const std::pair<int, std::vector<int>>& cand1, const std::pair<int, std::vector<int>>& cand2) {
               auto delta_rho1 = fabs(get_rho(vxyz[cand1.first][0], vxyz[cand1.first][1]) - pipe_rho);
               auto delta_rho2 = fabs(get_rho(vxyz[cand1.first][0], vxyz[cand1.first][1]) - pipe_rho);
               return delta_rho1 < delta_rho2;
            };
            it_min = std::min_element(candidates.begin(), candidates.end(), closest_to_pipe_vertex); 
         }
         fill_vertex_vecs(it_min->first);
         for(const auto& track_id : it_min->second)
         { fill_track_vecs(track_id); }
         new_tree->Fill();
      }
      clear_vecs();
      skip = false;
   }

   new_file->Write();
   new_file->Save();
}
