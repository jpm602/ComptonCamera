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
/// \file B1RunAction.hh
/// \brief Definition of the B1RunAction class

#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class B1RunAction : public G4UserRunAction
{
  public:
    B1RunAction();
    virtual ~B1RunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double edep); 
    void CountUseful(){numberUseful+=1;};
    void CountUseless(){numberUseless+=1;};
    void Count(){count+=1;};
    void PhotonScattererCount(){photonScattererCount+=1;};
    void PhotonAbsorberCount(){photonAbsorberCount+=1;};
    void OutputFolder(std::string folderName){fOutput = folderName;};

    void Count1ScatterEscape(){OneScatterEscape+=1;}; //George Remove if breaks
    void CountMoreScatterEscape(){MoreScatterEscape+=1;};
    void Count1Scatter(){OneScatter+=1;}; //George Remove if breaks
    void CountMoreScatter(){MoreScatter+=1;};
    void enter(){nEnterAbsorber+=1;}; //For single detector investigations
 
  private:
    G4bool ffirstWrite3; //This is needed
    G4bool fFirstWriteJack;
    int count = 0; 
    //int counter = 0;
    int numberUseful = 0; 
    int numberUseless = 0;
    int photonScattererCount;
    int photonAbsorberCount;
   
    int OneScatterEscape = 0; //George remove if breaks
    int MoreScatterEscape = 0;
    int OneScatter = 0; //George remove if breaks
    int MoreScatter = 0;
    int nEnterAbsorber = 0;

    //G4int totalNumber;
    G4Accumulable<G4double> fEdep;
    G4Accumulable<G4double> fEdep2;
    std::string fOutput;
};

#endif

