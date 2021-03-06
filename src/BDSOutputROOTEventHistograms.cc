#include "BDSOutputROOTEventHistograms.hh"

ClassImp(BDSOutputROOTEventHistograms)

BDSOutputROOTEventHistograms::BDSOutputROOTEventHistograms()
{
  TH1D::AddDirectory(kFALSE);
  TH2D::AddDirectory(kFALSE);
  TH3D::AddDirectory(kFALSE);
}

BDSOutputROOTEventHistograms::BDSOutputROOTEventHistograms(const BDSOutputROOTEventHistograms &rhs):
  TObject(rhs)
{
  // loop over 1d histograms
  for(auto h : rhs.histograms1D)
    {histograms1D.push_back(static_cast<TH1D*>(h->Clone()));}

  // loop over 2d histograms
  for(auto h : rhs.histograms2D)
    {histograms2D.push_back(static_cast<TH2D*>(h->Clone()));}

  // loop over 3d histograms
  for (auto h : rhs.histograms3D)
    {histograms3D.push_back(static_cast<TH3D*>(h->Clone()));}
}

BDSOutputROOTEventHistograms::~BDSOutputROOTEventHistograms()
{;}

#ifndef __ROOTBUILD__

G4int BDSOutputROOTEventHistograms::Create1DHistogram(G4String name, G4String title,
                                                      G4int nbins, G4double xmin, G4double xmax)
{
  this->histograms1D.push_back(new TH1D(name,title, nbins, xmin, xmax));
  return (G4int)this->histograms1D.size();
}

G4int BDSOutputROOTEventHistograms::Create1DHistogram(G4String name, G4String title,
                                                      std::vector<double>& edges)
{

  Double_t* edgesD = new Double_t[edges.size()];
  for(int i=0;i<(int)edges.size();++i) {
    edgesD[i] = edges[i];
//    G4cout << edgesD[i] << G4endl;
  }
  this->histograms1D.push_back(new TH1D(name,title,(Int_t)edges.size()-1,edgesD));
  delete[] edgesD;

  return (G4int)this->histograms1D.size();
}

G4int BDSOutputROOTEventHistograms::Create2DHistogram(G4String name, G4String title,
                                                      G4int nxbins, G4double xmin, G4double xmax,
                                                      G4int nybins, G4double ymin, G4double ymax)
{
  this->histograms2D.push_back(new TH2D(name,title, nxbins, xmin, xmax, nybins, ymin, ymax));
  return (G4int)this->histograms2D.size();
}

G4int BDSOutputROOTEventHistograms::Create2DHistogram(G4String name, G4String title,
                                                      std::vector<double>& xedges,
                                                      std::vector<double>& yedges)
{
  Double_t* xedgesD = new Double_t[xedges.size()];
  for(int i=0;i<(int)xedges.size();++i) {
    xedgesD[i] = xedges[i];
  }

  Double_t* yedgesD = new Double_t[yedges.size()];
  for(int i=0;i<(int)yedges.size();++i) {
    yedgesD[i] = yedges[i];
  }

  this->histograms2D.push_back(new TH2D(name.data(),title.data(), (Int_t)xedges.size()-1, xedgesD, (Int_t)yedges.size()-1, yedgesD));
  delete[] xedgesD;
  delete[] yedgesD;

  return (G4int)this->histograms2D.size();
}

G4int BDSOutputROOTEventHistograms::Create3DHistogram(G4String name, G4String title,
						      G4int nxbins, G4double xmin, G4double xmax,
						      G4int nybins, G4double ymin, G4double ymax,
						      G4int nzbins, G4double zmin, G4double zmax)
{
  histograms3D.push_back(new TH3D(name, title,
				  nxbins, xmin, xmax,
				  nybins, ymin, ymax,
				  nzbins, zmin, zmax));
  return (G4int)histograms3D.size();
}

G4int BDSOutputROOTEventHistograms::Create3DHistogram(G4String name, G4String title,
						      std::vector<double>& xedges,
						      std::vector<double>& yedges,
						      std::vector<double>& zedges)
{
  Double_t* xedgesD = new Double_t[xedges.size()];
  for(int i=0;i<(int)xedges.size();++i) {
    xedgesD[i] = xedges[i];
  }

  Double_t* yedgesD = new Double_t[yedges.size()];
  for(int i=0;i<(int)yedges.size();++i) {
    yedgesD[i] = yedges[i];
  }

  Double_t* zedgesD = new Double_t[zedges.size()];
  for(int i=0;i<(int)zedges.size();++i) {
    zedgesD[i] = zedges[i];
  }
  
  histograms3D.push_back(new TH3D(name.data(),title.data(),
				  (Int_t)xedges.size()-1, xedgesD,
				  (Int_t)yedges.size()-1, yedgesD,
				  (Int_t)zedges.size()-1, zedgesD));
  return (G4int)histograms3D.size();
}

void BDSOutputROOTEventHistograms::Fill1DHistogram(G4int histoId, G4double value,
                                                   G4double weight)
{
  this->histograms1D[histoId]->Fill(value,weight);
}

void BDSOutputROOTEventHistograms::Fill2DHistogram(G4int histoId, G4double xValue, G4double yValue,
                                                   G4double weight)
{
  this->histograms2D[histoId]->Fill(xValue,yValue,weight);
}

void BDSOutputROOTEventHistograms::Fill3DHistogram(G4int    histoId,
						   G4double xValue,
						   G4double yValue,
						   G4double zValue,
						   G4double weight)
{
  histograms3D[histoId]->Fill(xValue,yValue,zValue,weight);
}

void BDSOutputROOTEventHistograms::Flush()
{
  for (auto h : histograms1D)
    {h->Reset();}
  for (auto h : histograms2D)
    {h->Reset();}
  for (auto h : histograms3D)
    {h->Reset();}
}

#endif

void BDSOutputROOTEventHistograms::Add(BDSOutputROOTEventHistograms * /*rhs*/)
{
//   for(auto h : rhs->histograms1D )
//   {
// //    this->
//   }
}
