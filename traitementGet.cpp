#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    vector<string> listLogin;
    vector<string> listMdp;

    // En-tête
    cout << "Content-type: text/html\n\n";

    // Récupération des logins et mdp dans le fichier txt
    ifstream fichier("login.txt");
    string loginTrue, mdpTrue;

    if (fichier) {
        string line;
        while (getline(fichier, line)) {
            stringstream iss(line);
            iss >> loginTrue >> mdpTrue;
            listLogin.push_back(loginTrue);
            listMdp.push_back(mdpTrue);
        }
        fichier.close();
    }

    // Récupération des données envoyées via GET
    char* queryString = getenv("QUERY_STRING");

    string data = queryString != nullptr ? string(queryString) : "";

    string login = "", password = "";

    // Extraction des valeurs pour login et password
    int debutLogin = data.find("login=") + 6; 
    int finLogin = data.find("&"); 
    if (finLogin != string::npos) {
        login = data.substr(debutLogin, finLogin - debutLogin);
    }

    int debutPassword = data.find("password=") + 9;
    password = data.substr(debutPassword);

    // Vérifie si les logins et mdp sont dans la liste
    bool isOK = false;
    for (size_t i = 0; i < listLogin.size(); ++i) {
        if (listLogin[i] == login && listMdp[i] == password) {
            isOK = true;
            break;
        }
    }

    // Affichage
    if (isOK) {
        cout << "<html>\n";
        cout << "<head><title>Accueil</title></head>\n";
        cout << "<body>\n";
        cout << "<h1>Welcome " << login << " !</h1>\n";
        cout << "<p>Login : " << login << "</p>\n";
        cout << "<p>Mot de passe : " << password << "</p>\n";
        cout << "</body>\n";
        cout << "</html>\n";
    } else {
        cout << "<html>";
        cout << "<head><title>Erreur</title></head>";
        cout << "<body>";
        cout << "<h1>Erreur de connexion</h1>";
        cout << "<p>Votre login et mot de passe sont invalides. Veuillez réessayer.</p>";
        cout << "<form action='traitement.cgi' method='get'>";
        cout << "<div><label for='login'>Nom d'utilisateur: </label><input name='login' type='text' value='" << login << "'></div>";
        cout << "<div><label for='password'>Mot de passe: </label><input name='password' type='password' value='" << password << "'></div>";
        cout << "<button type='submit'>Valider</button></form></body></html>";
    }

    return 0;
}
