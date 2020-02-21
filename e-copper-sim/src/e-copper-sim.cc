#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include <G4UImanager.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>

namespace ecs {

class Application {
public:

	Application() {

	}

	void printBanner() {
		G4cout << G4endl
				<< "*************************************************************"
				<< G4endl << "Simulation of electron-induced copper films"
				<< G4endl << "Copyright Andrey Nakin <andrey.nakin@mail.ru>"
				<< G4endl
				<< "*************************************************************"
				<< G4endl << G4endl;
	}

	void run(int argc, char* argv[]) {
		printBanner();

#ifdef G4MULTITHREADED
		G4MTRunManager runManager;
		runManager.SetNumberOfThreads(2);
#else
		G4RunManager runManager;
#endif

		auto uiManager = G4UImanager::GetUIpointer();

		if (argc > 1) {
			// first argument is a script file name
			G4String const command = "/control/execute ";
			uiManager->ApplyCommand(command + argv[1]);
		} else {
			// no arguments passed to executable - run in visual mode
			auto const visManager = new G4VisExecutive("Quiet");
			visManager->Initialize();

			auto ui = new G4UIExecutive(argc, argv);
			uiManager->ApplyCommand("/control/execute vis.mac");
			ui->SessionStart();
			delete ui;
		}
	}

};

}

int main(int argc, char* argv[]) {
	ecs::Application app;
	app.run(argc, argv);
	return 0;

}
