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
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4VisAttributes.hh"

#include "B1DetectorMessenger.hh"

#include "G4UserLimits.hh" //George
#include "G4StepStatus.hh" //George
#include "G4StepPoint.hh"

#include <cmath> // Douglas

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(), 
  fScoringVolume(0),
  fScatXPos(0),
  fScatYPos(0),
  fScatZPos(0),
  fScatPolarR(0),
  fScatPolarPhi(0),
  fScatPolarTheta(0),
  fScatRotX(0),
  fScatRotY(0),
  fScatRotZ(0),
  fScatRad(0),
  fScatHeight(0),
  fScat2XPos(0),
  fScat2YPos(0),
  fScat2ZPos(0),
  fScat2PolarR(0),
  fScat2PolarPhi(0),
  fScat2PolarTheta(0),
  fScat2RotX(0),
  fScat2RotY(0),
  fScat2RotZ(0),
  fScat2Rad(0),
  fScat2Height(0),
  fScat2Bool(0),
  fDetXPos(0),
  fDetYPos(0),
  fDetZPos(0),
  fDetPolarR(0),
  fDetPolarPhi(0),
  fDetPolarTheta(0),
  fDetRotX(0),
  fDetRotY(0),
  fDetRotZ(0),
  fDetRad(0),
  fDetHeight(0),
  fDet2XPos(0),
  fDet2YPos(0),
  fDet2ZPos(0),
  fDet2PolarR(0),
  fDet2PolarPhi(0),
  fDet2PolarTheta(0),
  fDet2RotX(0),
  fDet2RotY(0),
  fDet2RotZ(0),
  fDet2Rad(0),
  fDet2Height(0),
  fDet2Bool(0),
  fDetectorMessenger(0)
{
//Material Definition  of Lanthanum(III) Bromide - by Ben
G4Isotope* iso79_Br = new G4Isotope("79_Br", 35, 79, 78.918*g/mole);
G4Isotope* iso81_Br = new G4Isotope("81_Br", 35, 81, 80.916*g/mole);
G4Isotope* iso138_La = new G4Isotope("138_La", 57, 138, 137.907*g/mole);
G4Isotope* iso139_La = new G4Isotope("139_La", 57, 139, 138.906*g/mole);

G4Element* Br = new G4Element("Bromide", "Br", 2);
Br->AddIsotope(iso79_Br, 50.69*perCent);
Br->AddIsotope(iso81_Br, 49.31*perCent);
G4Element* La = new G4Element("Lanthanum", "La", 2);
La->AddIsotope(iso138_La, 0.08881*perCent);
La->AddIsotope(iso139_La, 99.9119*perCent);

G4Material* LaBr = 
new G4Material("Lanthanum_Bromide", 5.06*g/cm3, 2, kStateSolid);
LaBr->AddElement( Br, 0.6036373016896684);
LaBr->AddElement( La, 0.39636269831033155);

//More Materials - George


 //G4NistManager* nist = G4NistManager::Instance();
 //G4Material* CeF3 = nist->FindOrBuildMaterial("G4_CERIUM_FLUORIDE");
 //G4Material* CI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
 //G4Material* CaF2 = nist->FindOrBuildMaterial("G4_CALCIUM_FLUORIDE");
 //G4Material* BaF2 = nist->FindOrBuildMaterial("G4_BARIUM_FLUORIDE");
 //G4Material* CdWO4 = nist->FindOrBuildMaterial("G4_CADMIUM_TUNGSTATE");

 //G4Element* Lu = nist->FindOrBuildElement("G4_Lu");
 //G4Element* Y = nist->FindOrBuildElement("G4_Y");
 //G4Element* Si = nist->FindOrBuildElement("G4_Si");
 //G4Element* O = nist->FindOrBuildElement("G4_O");
 //G4Material* LYSO = 
 //new G4Material("LYSO",  3.67*g/cm3, 4, kStateSolid);
 //LYSO->AddElement(Lu, 0.625); 
 //LYSO->AddElement(Y, 0.0529);
 //LYSO->AddElement(Si, 0.2385);
 //LYSO->AddElement(O, 0.0836);

 //G4Element* Pb = nist->FindOrBuildElement("G4_Pb");
 //G4Element* W  = nist->FindOrBuildElement("G4_W");
 //G4Material* PbWO4 = new G4Material("PbWO4",8.28,3);
 //PbWO4->AddElement(Pb,1);
 //PbWO4->AddElement(W,1);
 //PbWO4->AddElement(O,4);
 
fDetectorMessenger = new B1DetectorMessenger(this);
 
fScatXPos = 0;
fScatYPos = 0;
fScatZPos = 0;
fScatPolarR = 0;
fScatPolarPhi = 9000; // 9000 is a default value to get the code to ignore this if we use cartesian
fScatPolarTheta = 9000;
fScatRotX = 90*deg;
fScatRotY = 0;
fScatRotZ = 0;
fScatRad = 7*mm;
fScatHeight = 21.5*mm;

fScat2XPos = 10*cm;
fScat2YPos = 0;
fScat2ZPos = 0;
fScat2PolarR = 0;
fScat2PolarPhi = 9000; // 9000 is a default value to get the code to ignore this if we use cartesian
fScat2PolarTheta = 9000;
fScat2RotX = 90*deg;
fScat2RotY = 0;
fScat2RotZ = 0;
fScat2Rad = 7*mm;
fScat2Height = 21.5*mm;
fScat2Bool = false;

fDetXPos = -12.15*cm;
fDetYPos = 0;
fDetZPos = 26.205*cm;
fDetPolarR = 0;
fDetPolarPhi = 9000;
fDetPolarTheta = 9000;
fDetRotX = 0;
fDetRotY = 0;
fDetRotZ = 0;
fDetRad = 1.905*cm;
fDetHeight = 1.905*cm;

fDet2XPos = 12.15*cm;
fDet2YPos = 0;
fDet2ZPos = 26.205*cm;
fDet2PolarR = 0;
fDet2PolarPhi = 9000;
fDet2PolarTheta = 9000;
fDet2RotX = 0;
fDet2RotY = -30*deg;
fDet2RotZ = 0;
fDet2Rad = 1.905*cm;
fDet2Height = 1.905*cm;
fDet2Bool = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{
  delete fDetectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{
  return ConstructVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::ConstructVolumes()
{
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  
  // Envelope parameters
  //
  G4double env_sizeXY = 100*cm, env_sizeZ = 200*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =  new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
  
  G4VisAttributes* logicWorldVis = new G4VisAttributes();
  logicWorldVis->SetVisibility(false);
  logicWorld->SetVisAttributes(logicWorldVis);
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //
  G4RotationMatrix* rotEnv = new G4RotationMatrix();
  //rotEnv->rotateX(90*deg);
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
  
  G4VisAttributes* logicEnvVis = new G4VisAttributes();
  logicEnvVis->SetVisibility(false);
  logicEnv->SetVisAttributes(logicEnvVis);

               
  new G4PVPlacement(rotEnv,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  G4RotationMatrix* rot1 = new G4RotationMatrix();
  rot1->rotateX(fScatRotX);
  rot1->rotateY(fScatRotY);
  rot1->rotateZ(fScatRotZ);

  G4RotationMatrix* rot3 = new G4RotationMatrix();
  rot3->rotateX(fScat2RotX);
  rot3->rotateY(fScat2RotY);
  rot3->rotateZ(fScat2RotZ);
  
  
  //
  //     
  // Scatterer
  //  
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  G4ThreeVector* pos1 = new G4ThreeVector(fScatXPos, fScatYPos, fScatZPos);
  if(fScatPolarR!=0)
    {
      pos1->setMag(fScatPolarR);
    }
  if(fScatPolarPhi!=9000)
    {
      pos1->setTheta(fScatPolarPhi);
    }
  if(fScatPolarTheta!=9000)
    {// theta of scatterer by Doug
      pos1->setPhi(fScatPolarTheta);
    }
        
  // Tube section shape       
  G4double shape1_rmina =  0.*cm, shape1_rmaxa = fScatRad;
  G4double shape1_hz = fScatHeight;
  G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  G4Tubs* solidShape1 =    
    new G4Tubs("Shape1", shape1_rmina, shape1_rmaxa, shape1_hz, shape1_phimin, shape1_phimax);
                      
  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Scatterer");           //its name
               
  new G4PVPlacement(rot1,                    //rotation
                    G4ThreeVector(pos1->x(), pos1->y(), pos1->z()),  //at position
                    logicShape1,             //its logical volume
                    "Scatterer",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //
  //     
  // Scatterer 2 - By Jack
  //
  if (fScat2Bool == true)
    {
      G4Material* shape3_mat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
      G4ThreeVector* pos3 = new G4ThreeVector(fScat2XPos, fScat2YPos, fScat2ZPos);
      if(fScat2PolarR!=0)
	{
	  pos3->setMag(fScat2PolarR);
	}
      if(fScat2PolarPhi!=9000)
	{
	  pos3->setTheta(fScat2PolarPhi);
	}
      if(fScat2PolarTheta!=9000)
	{
	  pos3->setPhi(fScat2PolarTheta);
	}
        
      // Tube section shape       
      G4double shape3_rmina =  0.*cm, shape3_rmaxa = fScat2Rad;
      G4double shape3_hz = fScat2Height;
      G4double shape3_phimin = 0.*deg, shape3_phimax = 360.*deg;
      G4Tubs* solidShape3 =    
	new G4Tubs("Shape3", shape3_rmina, shape3_rmaxa, shape3_hz, shape3_phimin, shape3_phimax);
                      
      G4LogicalVolume* logicShape3 =                         
	new G4LogicalVolume(solidShape3,         //its solid
			    shape3_mat,          //its material
			    "Scatterer");           //its name
               
      new G4PVPlacement(rot3,                    //rotation
			G4ThreeVector(pos3->x(), pos3->y(), pos3->z()),  //at position
			logicShape3,             //its logical volume
			"Scatterer",                //its name
			logicEnv,                //its mother  volume
			false,                   //no boolean operation
			1,                       //copy number
			checkOverlaps);          //overlaps checking
    }


  //
  // Body (George) 
  //

  G4bool wantBody = false; 
  if(wantBody==true){
	G4Material* bodyMat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
	G4ThreeVector* bodyPos = new G4ThreeVector(0.*cm,0.*cm,0.*cm); //needs to be around source
	G4double bodyHeight = 10*cm;
	G4double bodyRadius = 18*cm; //Average according to some website - get proper source
	G4Tubs* bodyShape =    
    new G4Tubs("Body", 0*cm, bodyRadius/2, bodyHeight/2, 0*deg, 360*deg);
	G4LogicalVolume* bodyVolume = new G4LogicalVolume(bodyShape,bodyMat,"Body"); 
	new G4PVPlacement(rot1,                    //rotation
                    G4ThreeVector(bodyPos->x(), bodyPos->y(), bodyPos->z()),  //at position
                    bodyVolume,             //its logical volume
                    "Body",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
	};

  //     
  // Absorber
  //
  G4ThreeVector* pos2 = new G4ThreeVector(fDetXPos, fDetYPos, fDetZPos);
  if(fDetPolarR!=0)
    {
      pos2->setMag(fDetPolarR);
    }
  if(fDetPolarPhi!=9000)
    {
      pos2->setTheta(fDetPolarPhi);
    }
  if(fDetPolarTheta!=9000)
    {// theta of absorber by Doug
      pos2->setPhi(fDetPolarTheta);
    }
  G4Material* shape2_mat = nist->FindOrBuildMaterial("Lanthanum_Bromide");
  G4RotationMatrix* rot2 = new G4RotationMatrix();
  rot2->rotateX(fDetRotX);
  rot2->rotateY(fDetRotY);
  rot2->rotateZ(fDetRotZ);

  G4double shape2_rmina =  0.*cm, shape2_rmaxa = fDetRad;
  G4double shape2_hz = fDetHeight;
  G4double shape2_phimin = 0.*deg, shape2_phimax = 360.*deg;
  G4Tubs* solidShape2 =    new G4Tubs("Shape2",
    shape2_rmina, shape2_rmaxa, shape2_hz,
    shape2_phimin, shape2_phimax);
                
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Absorber");           //its name
               
  new G4PVPlacement(rot2,                       //no rotation
                    G4ThreeVector(pos2->x(), pos2->y(), pos2->z()),        		//at position
                    logicShape2,             //its logical volume
                    "Absorber",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //     
  // Absorber 2 - by Jack
  //
  if (fDet2Bool == true)
    {
      G4ThreeVector* pos4 = new G4ThreeVector(fDet2XPos, fDet2YPos, fDet2ZPos);
      if(fDet2PolarR!=0)
	{
	  pos4->setMag(fDet2PolarR);
	}
      if(fDet2PolarPhi!=9000)
	{
	  pos4->setTheta(fDet2PolarPhi);
	}
      if(fDet2PolarTheta!=9000)
	{
	  pos4->setPhi(fDet2PolarTheta);
	}
      G4Material* shape4_mat = nist->FindOrBuildMaterial("Lanthanum_Bromide");
      G4RotationMatrix* rot4 = new G4RotationMatrix();
      rot4->rotateX(fDet2RotX);
      rot4->rotateY(fDet2RotY);
      rot4->rotateZ(fDet2RotZ);

      G4double shape4_rmina =  0.*cm, shape4_rmaxa = fDet2Rad;
      G4double shape4_hz = fDet2Height;
      G4double shape4_phimin = 0.*deg, shape4_phimax = 360.*deg;
      G4Tubs* solidShape4 =    new G4Tubs("Shape4",
					  shape4_rmina, shape4_rmaxa, shape4_hz,
					  shape4_phimin, shape4_phimax);
                
      G4LogicalVolume* logicShape4 =                         
	new G4LogicalVolume(solidShape4,         //its solid
			    shape4_mat,          //its material
			    "Absorber");           //its name
               
      new G4PVPlacement(rot4,                       //no rotation
			G4ThreeVector(pos4->x(), pos4->y(), pos4->z()),        		//at position
			logicShape4,             //its logical volume
			"Absorber",                //its name
			logicEnv,                //its mother  volume
			false,                   //no boolean operation
			1,                       //copy number
			checkOverlaps);          //overlaps checking
    }
  
  
  //Varying step length depending on the logical volume 
  G4double stepLength = 0.0005*mm;
  G4UserLimits* maxStep = new G4UserLimits(stepLength); 
  logicShape1->SetUserLimits(maxStep);
  logicShape2->SetUserLimits(maxStep);


  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// By Jack
void B1DetectorConstruction::SetScatXPos(G4double val)
{
  fScatXPos = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScatYPos(G4double val)
{
  fScatYPos = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScatZPos(G4double val)
{
  fScatZPos = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScatPolarR(G4double val)
{
  fScatPolarR = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScatPolarPhi(G4double val)
{
  fScatPolarPhi = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScatPolarTheta(G4double val)
{
  fScatPolarTheta = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScatRotX(G4double val)
{
  fScatRotX = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScatRotY(G4double val)
{
  fScatRotY = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScatRotZ(G4double val)
{
  fScatRotZ = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScatRad(G4double val)
{
  fScatRad = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScatHeight(G4double val)
{
  fScatHeight = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScat2XPos(G4double val)
{
  fScat2XPos = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScat2YPos(G4double val)
{
  fScat2YPos = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScat2ZPos(G4double val)
{
  fScat2ZPos = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScat2PolarR(G4double val)
{
  fScat2PolarR = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScat2PolarPhi(G4double val)
{
  fScat2PolarPhi = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScat2PolarTheta(G4double val)
{
  fScat2PolarTheta = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScat2RotX(G4double val)
{
  fScat2RotX = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScat2RotY(G4double val)
{
  fScat2RotY = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScat2RotZ(G4double val)
{
  fScat2RotZ = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScat2Rad(G4double val)
{
  fScat2Rad = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScat2Height(G4double val)
{
  fScat2Height = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetScat2Bool(G4bool val)
{
  fScat2Bool = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDetXPos(G4double val)
{
  fDetXPos = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDetYPos(G4double val)
{
  fDetYPos = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDetZPos(G4double val)
{
  fDetZPos = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDetPolarR(G4double val)
{
  fDetPolarR = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDetPolarPhi(G4double val)
{
  fDetPolarPhi = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDetPolarTheta(G4double val)
{
  fDetPolarTheta = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDetRotX(G4double val)
{
  fDetRotX = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDetRotY(G4double val)
{
  fDetRotY = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDetRotZ(G4double val)
{
  fDetRotZ = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDetRad(G4double val)
{
  fDetRad = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDetHeight(G4double val)
{
  fDetHeight = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDet2XPos(G4double val)
{
  fDet2XPos = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDet2YPos(G4double val)
{
  fDet2YPos = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDet2ZPos(G4double val)
{
  fDet2ZPos = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDet2PolarR(G4double val)
{
  fDet2PolarR = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDet2PolarPhi(G4double val)
{
  fDet2PolarPhi = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDet2PolarTheta(G4double val)
{
  fDet2PolarTheta = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDet2RotX(G4double val)
{
  fDet2RotX = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDet2RotY(G4double val)
{
  fDet2RotY = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDet2RotZ(G4double val)
{
  fDet2RotZ = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDet2Rad(G4double val)
{
  fDet2Rad = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDet2Height(G4double val)
{
  fDet2Height = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::SetDet2Bool(G4bool val)
{
  fDet2Bool = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructVolumes());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
