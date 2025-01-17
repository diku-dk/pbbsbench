// This code is part of the Problem Based Benchmark Suite (PBBS)
// Copyright (c) 2011 Guy Blelloch and the PBBS team
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights (to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <algorithm>
#include "parlay/parallel.h"
#include "parlay/primitives.h"
#include "parlay/random.h"
#include "common/geometry.h"
#include "../utils/NSGDist.h"  
#include "../utils/types.h"
#include "pynn_index2.h"
#include "../utils/beamSearch.h"  
#include "../utils/indexTools.h"
#include "../utils/stats.h"

extern bool report_stats;

template<typename T>
void checkRecall(pyNN_index<T>& I,
		  parlay::sequence<Tvec_point<T>*> &v,
		  parlay::sequence<Tvec_point<T>*> &q,
		  parlay::sequence<ivec_point> groundTruth,
		  int k,
		  int beamQ,
		  float cut,
      unsigned d) {
  parlay::internal::timer t;
  int r = 10;
  int dist_cmps = beamSearchRandom(q, v, beamQ, k, d, cut);
  t.next_time();
  beamSearchRandom(q, v, beamQ, k, d, cut);
  float query_time = t.next_time();
  float recall = 0.0;
  if (groundTruth.size() > 0) {
    size_t n = q.size();
    int numCorrect = 0;
    for(int i=0; i<n; i++){
      std::set<int> reported_nbhs;
      for(int l=0; l<r; l++)
	reported_nbhs.insert((q[i]->ngh)[l]);
      for(int l=0; l<r; l++)
	if (reported_nbhs.find((groundTruth[i].coordinates)[l])
	    != reported_nbhs.end())
	  numCorrect += 1;
    }
    recall = static_cast<float>(numCorrect)/static_cast<float>(r*n);
  }
  std::cout << "k = " << k << ", Q = " << beamQ << ", cut = " << cut
	    << ", throughput = " << (q.size()/query_time) << "/second";
  if (groundTruth.size() > 0)
    std::cout << ", recall = " << recall << std::endl;
  else std::cout << std::endl;
  if(report_stats) std::cout << "Distance comparisons: " << dist_cmps << std::endl;
}

template<typename T>
void ANN(parlay::sequence<Tvec_point<T>*> &v, int k, int K, int cluster_size, int beamSizeQ, double num_clusters, double alpha,
  parlay::sequence<Tvec_point<T>*> &q, parlay::sequence<ivec_point> groundTruth) {
  parlay::internal::timer t("ANN",report_stats); 
  {
    
    unsigned d = (v[0]->coordinates).size();
    using findex = pyNN_index<T>;
    findex I(K, d, .05);
    std::cout << "Degree bound K " << K << std::endl;
    std::cout << "Cluster size " << cluster_size << std::endl;
    std::cout << "Number of clusters " << num_clusters << std::endl;
    // std::cout << "Change parameter " << delta << std::endl; 
    I.build_index(v, cluster_size, (int) num_clusters, alpha);
    t.next("Built index");

    std::cout << "num queries = " << q.size() << std::endl;
    std::vector<int> beams = {15, 20, 30, 50, 75, 100, 125, 250, 500};
    std::vector<int> allk = {10, 15, 20, 30, 50, 100};
    std::vector<float> cuts = {1.1, 1.125, 1.15, 1.175, 1.2, 1.25};
    for (float cut : cuts)
      for (float Q : beams) 
        checkRecall(I, v, q, groundTruth, 10, Q, cut, d);

    std::cout << " ... " << std::endl;

    for (float cut : cuts)
      for (int kk : allk)
        checkRecall(I, v, q, groundTruth, kk, 500, cut, d);

    // check "best accuracy"
    checkRecall(I, v, q, groundTruth, 100, 1000, 10.0, d);

    beamSearchRandom(q, v, beamSizeQ, k, d);
    t.next("Found nearest neighbors");
    if(report_stats){
      //average numbers of nodes searched using beam search
      graph_stats(v);
      query_stats(q);
      t.next("stats");
    }
  };
}


template<typename T>
void ANN(parlay::sequence<Tvec_point<T>*> v, int K, int cluster_size, double num_clusters, double alpha) {
  parlay::internal::timer t("ANN",report_stats); 
  { 
    // std::cout << K << std::endl;
    // std::cout << cluster_size << std::endl;
    // std::cout << num_clusters << std::endl;
    // std::cout << delta << std::endl;
    unsigned d = (v[0]->coordinates).size();
    using findex = pyNN_index<T>;
    findex I(K, d, .05);
    I.build_index(v, cluster_size, (int) num_clusters, alpha);
    t.next("Built index");
    if(report_stats){
      graph_stats(v);
      t.next("stats");
    }
  };
}
