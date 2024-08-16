#include <iostream>
#include <cstdlib> 
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;
int main() {
    vector<string> listLogin;
    vector<string> listMdp;
    //En tete
    cout << "Content-type: text/html\n\n";
    //Recuperation du login et mdp dans le fichier txt
    ifstream fichier("login.txt");
    string loginTrue;
    string mdpTrue;
    if(fichier){
        while (fichier)
        {
            string line;
            getline(fichier,line);
            stringstream iss(line);
            iss >>loginTrue >> mdpTrue;
            listLogin.push_back(loginTrue);
            listMdp.push_back(mdpTrue);
        }
        fichier.close();
    }
    // Longueur des données envoyées par le formulaire
    char* contentLength = getenv("CONTENT_LENGTH");
    int length = 0;

    // Si la longueur existe, on la convertit en entier
    if (contentLength != nullptr) {
        length = atoi(contentLength); // Convertit la chaîne en entier
    }

    // LEcture des donnees dans le stdin
    string data;
    data.resize(length); 
    cin.read(&data[0], length); 

    string login = "";
    string password = "";

    // EXTRACTION DES VALEURS POUR login et password
    int debutLogin = data.find("login=") + 6; 
    int finLogin = data.find("&"); 
    login = data.substr(debutLogin, finLogin - debutLogin);

    int debutPassword = data.find("password=") + 9; // 9 pour ignorer "password="
    password = data.substr(debutPassword);
    //Vérifie si les logins et mdp sont dans la liste
    bool isOK = false;
    for (int i = 0; i < listLogin.size(); ++i) {
        if (listLogin[i] == login && listMdp[i] == password) {
            isOK = true;
            break;
        }
    }
    if (isOK)
    {
    //AFFICHAGE
        cout << "<html>\n";
        cout << "<head><title>Accueil</title></head>\n";
        cout << "<body>\n";
        cout << "<h1>Welcome "<<login<<" !</h1>\n";
        cout << "<p>Login : " << login << "</p>\n";
        cout << "<p>Mot de passe : " << password << "</p>\n";
        cout << "</body>\n";
        cout << "</html>\n";
    }
    else{
        cout << "<html>";
        cout << "<head><title>Erreur</title></head>";
        cout << "<body>";
        cout << "<h1>Erreur de connexion</h1>";
        cout << "<p>Votre login et mot de passe sont invalides. Veuillez reessayer.</p>";
        cout << "<form action='traitement.cgi' method='post'>";
        cout<<"<div><label for='login'>Nom d'utilisateur: </label><input name='login' type='text' value="<<login<<"></div>";
        cout<<"<div><label for='password'>Mot de passe: </label><input name='password' type='password' value="<<password<<"></div>";
        cout << "<button type='submit'>Valider</button></form></body></html>";
    }
    return 0;
}
