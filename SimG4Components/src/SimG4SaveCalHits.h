#ifndef SIMG4COMPONENTS_G4SAVECALHITS_H
#define SIMG4COMPONENTS_G4SAVECALHITS_H

// STL
#include <vector>
#include <string>

// Gaudi
#include "GaudiAlg/GaudiTool.h"

// k4FWCore
#include "k4FWCore/DataHandle.h"
#include "k4FWCore/MetaDataHandle.h"
#include "k4Interface/IGeoSvc.h"
#include "k4Interface/ISimG4SaveOutputTool.h"

// EDM4hep
#include "edm4hep/SimCalorimeterHitCollection.h"

/** @class SimG4SaveCalHits SimG4Components/src/SimG4SaveCalHits.h SimG4SaveCalHits.h
 *
 *  Save calorimeter hits tool.
 *  All collections passed in the job options will be saved (\b'readoutNames').
 *  Readout name is defined in DD4hep XML file as the attribute 'readout' of 'detector' tag.
 *  If (\b'readoutNames') contain no elements or names that do not correspond to any hit collection,
 *  tool will fail at initialization.
 *  [For more information please see](@ref md_sim_doc_geant4fullsim).
 *
 *  @author Anna Zaborowska
 */

class SimG4SaveCalHits : public GaudiTool, virtual public ISimG4SaveOutputTool {
public:
  explicit SimG4SaveCalHits(const std::string& aType, const std::string& aName, const IInterface* aParent);
  virtual ~SimG4SaveCalHits();
  /**  Initialize.
   *   @return status code
   */
  virtual StatusCode initialize();
  /**  Finalize.
   *   @return status code
   */
  virtual StatusCode finalize();
  /**  Save the data output.
   *   Saves the calorimeter hits from the collections as specified in the job options in \b'readoutNames'.
   *   @param[in] aEvent Event with data to save.
   *   @return status code
   */
  virtual StatusCode saveOutput(const G4Event& aEvent) final;

private:
  /// Pointer to the geometry service
  ServiceHandle<IGeoSvc> m_geoSvc;
  /// Output handle for calo hits
  DataHandle<edm4hep::SimCalorimeterHitCollection> m_caloHits{
      "CaloHits", Gaudi::DataHandle::Writer, this};
  /// Output handle for cell ID encoding string
  MetaDataHandle<std::string> m_cellIDEncoding{
      m_caloHits, "CellIDEncodingString", Gaudi::DataHandle::Writer};
  /// Name of the readouts (hits collections) to save, deprecated
  Gaudi::Property<std::vector<std::string>> m_readoutNames{
      this, "readoutNames", {}, "[Deprecated] Names of the readouts (hits collections) to save"};
  /// Name of the readout (hits collection) to save
  Gaudi::Property<std::string> m_readoutName {
      this, "readoutName", {}, "Name of the readout (hits collection) to save"};
};

#endif /* SIMG4COMPONENTS_G4SAVECALHITS_H */
