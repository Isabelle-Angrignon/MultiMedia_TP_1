#pragma once
#include "Singleton.h"
#include "dispositif.h" 
#include "Camera.h"

#include <vector>
#include "Objet3D.h"
#include "Bloc.h"
#include "BlocEffet1.h"
#include "DIManipulateur.h"
#include "GestionnaireDeTextures.h"
#include "Terrain.h"

namespace PM3D
{

	const int IMAGESPARSECONDE=20;

    //
	//   TEMPLATE�: CMoteur
	//
	//   BUT�: Template servant � construire un objet Moteur qui implantera les
	//         aspects "g�n�riques" du moteur de jeu
	//
	//   COMMENTAIRES�:
	//
	//        Comme plusieurs de nos objets repr�senteront des �l�ments uniques 
	//		  du syst�me (ex: le moteur lui-m�me, le lien vers 
	//        le dispositif Direct3D), l'utilisation d'un singleton 
	//        nous simplifiera plusieurs aspects.
	//
	template <class T, class TClasseDispositif> class CMoteur :public CSingleton<T>
	{
	public:

		CCamera camera;

		CDIManipulateur& GetGestionnaireDeSaisie() { return GestionnaireDeSaisie; }

		virtual void Run()
		{
		bool bBoucle=true;

			while (bBoucle)
			{
				// Propre � la plateforme - (Conditions d'arr�t, interface, messages)
				bBoucle = RunSpecific();	

				// appeler la fonction d'animation
				if (bBoucle) bBoucle = Animation();
			}
		}
		
		virtual int Initialisations()
		{
			// Propre � la plateforme
			InitialisationsSpecific();

			// * Initialisation du dispositif de rendu
			pDispositif = CreationDispositifSpecific( CDS_FENETRE );

			// * Initialisation de la sc�ne
			InitScene();

			// * Initialisation des param�tres de l'animation et 
			//   pr�paration de la premi�re image
			InitAnimation();

			return 0;
		}

		virtual bool Animation()
		{
		__int64 TempsCourant;
		float TempsEcoule;

			// m�thode pour lire l'heure et calculer le 
			// temps �coul�
			TempsCourant = GetTimeSpecific();

			// Est-il temps de rendre l'image?
			if (TempsCourant > TempsSuivant)
			{
				// Affichage optimis� 
				pDispositif->Present(); 

				TempsEcoule=static_cast<float>(TempsCourant-TempsPrecedent) 
							* static_cast<float>(EchelleTemps);

				// On pr�pare la prochaine image
				AnimeScene(TempsEcoule);

				// On rend l'image sur la surface de travail 
   				// (tampon d'arri�re plan)
				RenderScene();

				// Calcul du temps du prochain affichage
				TempsPrecedent=TempsCourant;
				TempsSuivant = TempsCourant + EcartTemps;
			}

			return true;
		}

		XMMATRIX GetMatView() { return matView; }
		XMMATRIX GetMatProj() { return matProj; }
		XMMATRIX GetMatViewProj() { return matViewProj; }

    protected :

		CDIManipulateur GestionnaireDeSaisie;

        // Constructeur par d�faut
		CMoteur(void){}
	
        // Destructeur
		~CMoteur(void)
		{
			Cleanup();
		}

		// Sp�cifiques - Doivent �tre implant�s
		virtual bool RunSpecific()=0;
		virtual int InitialisationsSpecific()=0;
		virtual __int64 GetTimeSpecific()=0;
		virtual TClasseDispositif* CreationDispositifSpecific(const CDS_MODE cdsMode)=0;
		virtual void BeginRenderSceneSpecific()=0;
		virtual void EndRenderSceneSpecific()=0;

		// Autres fonctions
		virtual int InitAnimation()
		{
			TempsSuivant = GetTimeSpecific();
			EchelleTemps = 0.001; 
			EcartTemps = 1000/IMAGESPARSECONDE;
			TempsPrecedent = TempsSuivant; 

			// premi�re Image
			RenderScene();

			return true;
		}

		// Fonctions de rendu et de pr�sentation de la sc�ne
		virtual bool RenderScene()
		{
			BeginRenderSceneSpecific();

			// Appeler les fonctions de dessin de chaque objet de la sc�ne
			std::vector<CObjet3D*>::iterator It;

			for (It = ListeScene.begin(); It != ListeScene.end(); It++)
			{
					(*It)->Draw();
			}

			EndRenderSceneSpecific();
			return true;
		}


		virtual void Cleanup()
		{
			// d�truire les objets
			std::vector<CObjet3D*>::iterator It;

			for (It = ListeScene.begin(); It != ListeScene.end();It++)
			{
				delete *It;
			}

			ListeScene.clear();
			
			// D�truire le dispositif
			if (pDispositif) 
			{
				delete pDispositif;
				pDispositif = NULL;
			}
		}

	virtual int InitScene()
	{
		// Initialisation des objets 3D - cr�ation et/ou chargement
		if (!InitObjets()) return 1;
	
		float champDeVision = XM_PI/4; 	// 45 degr�s
		float ratioDAspect = pDispositif->GetLargeur()/pDispositif->GetHauteur();
		//  raproch�/�loign�, garder 7 chiffres significatif
		float planRapproche = 0.1f;  // 0.1 jamais 0. etait 2.0
		float planEloigne = 400.0f;  //  etait 20.0... le plus petit possible
		
		matProj = XMMatrixPerspectiveFovRH( 
									champDeVision,
									ratioDAspect,
									planRapproche,
									planEloigne );


		camera.Init(XMVectorSet(128.0f, -10.0f, 10.0f, 1.0f),
			XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f),
			XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f),
			&matView, &matProj, &matViewProj );

		camera.Update();

		return 0;
	}

	bool InitObjets()
	{
		//CBlocEffet1* pBloc;
		CTerrain* pTerrain;

		//Cr�ation d'un terrain � partir de notre fichier converti...
		pTerrain = new CTerrain("Converti.ter", pDispositif);
		pTerrain->SetTexture(TexturesManager.GetNewTexture(L"Texture_Gravier.dds", pDispositif));

		// Cr�ation d'un cube de 2 X 2 X 2 unit�s
		// Le bloc est cr�� dans notre programme et sur le dispositif
		//pBloc = new CBlocEffet1( 2, 2, 2, pDispositif );
		
		// Puis, il est ajout� � la sc�ne
		//ListeScene.push_back(pBloc);
		ListeScene.push_back(pTerrain);
				
		return true;
	}

	bool AnimeScene(float tempsEcoule)
	{
		// Prendre en note le statut du clavier
		GestionnaireDeSaisie.StatutClavier();

		camera.Bouger(tempsEcoule);

		std::vector<CObjet3D*>::iterator It;

	    for (It = ListeScene.begin(); It != ListeScene.end();It++)
		{
			(*It)->Anime(tempsEcoule);
		}

		return true;
	}


	protected:
		// Variables pour le temps de l'animation
		__int64 TempsSuivant;
		__int64 TempsPrecedent;
		unsigned long EcartTemps;
		double EchelleTemps;

		// Le dispositif de rendu
		TClasseDispositif* pDispositif;


		// La seule sc�ne
		std::vector<CObjet3D*> ListeScene;

		// Les matrices
		XMMATRIX matView;
		XMMATRIX matProj;
		XMMATRIX matViewProj;

		CGestionnaireDeTextures TexturesManager;


    };


} // namespace PM3D

	