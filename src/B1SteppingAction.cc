//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4UserLimits.hh"
#include "G4SystemOfUnits.hh"

#include "G4Track.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{ 
  // track runtime of event by summing delta times in each step - by Jack
  G4double deltaTime = step->GetDeltaTime();
  fEventAction->TotalTime(deltaTime);
  // get physical and logical volume of the current step
  G4VPhysicalVolume* volumePhys 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume();
  G4LogicalVolume* volume = volumePhys->GetLogicalVolume();

  //Code to fix Segmentation Faults
  G4String procName = "";
  G4StepPoint* preStep = step->GetPreStepPoint();
  if(preStep!= nullptr)
  {
    const G4VProcess* proc = preStep->GetProcessDefinedStep();
    if(proc != nullptr)
    {
      procName = proc->GetProcessName();
    }
  }


  if (volume->GetName() != "Scatterer" && volume->GetName() != "Absorber") return;

  // collect energy deposited in step - originally by Jack, generalised with copy number by Douglas
  // scatterer energy
  // get copy number if multiple scatter detectors
  if (volume->GetName() == "Scatterer")
    {
      // Investigating energy in each scatter of a double Compton coincidence event - Jack
      G4String procName2 = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
      if(procName2 == "compt")
	{
	  G4double scatterEnergy = step->GetDeltaEnergy();
	  fEventAction->ScatterEnergy(scatterEnergy);
	}

      
      procName2 = "";
      procName2 = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
      if(procName2=="compt")
      {
      fEventAction->totalComptons(); //By george
      G4ThreeVector preMomentum = step->GetPreStepPoint()->GetMomentum(); 
      G4ThreeVector postMomentum = step->GetPostStepPoint()->GetMomentum(); //George
      G4double deltaComptonEnergy = step->GetDeltaEnergy(); //George
      fEventAction->DeltaMomentum(preMomentum, postMomentum); //Test
      fEventAction->DeltaComptonEnergy(deltaComptonEnergy); //George
      } //George
      G4double stepLength = step->GetStepLength();
      G4double edepStep = step->GetTotalEnergyDeposit();
      int copyNo = volumePhys->GetCopyNo();
      fEventAction->AddEdepScatterer(edepStep, copyNo);
      G4double timeScatterer = step->GetTrack()->GetGlobalTime();
      fEventAction->TimeScatterer(timeScatterer, copyNo);
      

    // Finding change in momentum and energy for calcuting scatter angle. By Doug. 


      // Finding total number of photons that enter the scatterer to test fraction that interact - by Jack
      if (step->GetTrack()->GetParentID()==0 && step->IsFirstStepInVolume()==true)
	{
	  fEventAction->PhotonScatterer();
	}

	if (procName == "compt")
	{
		G4ThreeVector Pos = step->GetPreStepPoint()->GetPosition();
		fEventAction->Vector(Pos, copyNo);
		fEventAction->Count();
	}

	// Finding details of processes that cause energy deposition that aren't Compton to solve the 0 scatter coincidence problem - by Jack
	else
	{
	  if (edepStep!=0 && procName != "StepLimiter")
	    {
	      fEventAction->ZeroScatterInfo(edepStep, procName, step->GetPreStepPoint()->GetPosition());
	    }
	}
    }



  // absorber energy
  if (volume->GetName() == "Absorber")
    { 
      //if(step->IsLastStepInVolume()==true && procName=="Transportation"){fEventAction->exit();};
      if(step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary){fEventAction->exit();};
      G4String photEffect = "";
      photEffect = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
      //std::cout<<photEffect<<"\n";
      //if(procName == "compt"){fEventAction->totalComptons();}; //George.
      //if(step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary){fEventAction->exit();};
      //if(step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary){fRunAction->enter();};
      // George^ there's a bool in EventAction and the photon is only counted if it comptons once and exits
      //if(step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary)
 	//{G4double energyExit = step->GetPostStepPoint()->GetTotalEnergy();
	 //fEventAction->EnergyExit(energyExit);};
      G4double edepStep = step->GetTotalEnergyDeposit();
      int copyNo = volumePhys->GetCopyNo();
      G4double timeDetector = step->GetTrack()->GetGlobalTime();
      fEventAction->AddEdepDetector(edepStep, copyNo);
      fEventAction->TimeDetector(timeDetector, copyNo); //debugging


if(step->GetTrack()->GetParentID()==0 && step->GetPostStepPoint()->GetKineticEnergy() <= 0.1*keV && step->GetPostStepPoint()->GetStepStatus() != fGeomBoundary)
		{
		G4ThreeVector Pos2 = step->GetPreStepPoint()->GetPosition();
		fEventAction->Vector2(Pos2, copyNo);
		fEventAction->Proc2(procName);
		} 
	// Finding total number of photons that enter the absorber to test fraction that interact - by Jack
	if (step->GetTrack()->GetParentID()==0 && step->IsFirstStepInVolume()==true)
	{
	  fEventAction->PhotonAbsorber();
	}
    }
}

