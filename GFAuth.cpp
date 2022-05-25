// GFAuth.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <curl/curl.h>


using namespace std;

class PRBAuth {

private:
	string pass;
	string user;

public:
	PRBAuth(string vuser, string vpass)
	{
		user = vuser;
		pass = vpass;
	}

	string getParams()
	{
		string p = "edit[id]=" + user + "&edit[pass]=" + pass + "&edit[remember]=0";
		p = p + "&edit[destination]=https://api.aeriagames.com/dialog/oauth/signup?response_type=code&client_id=0ad0734dc5df644018b5fbfc8265ec6c05bb218dc&state=xyz&lang=es&Scope=scope_general,scope_billing";
		p = p + "&op=Iniciar sesión&edit[method]=oauth2&edit[form_id]=account_login";

		return p;
	}

	void sendForm()
	{
		cout << "Auth en progreso, esperando respuesta del servidor..." << endl;

		curl_global_init(CURL_GLOBAL_ALL);

		CURL *curl;
		CURLcode res;
		curl = curl_easy_init();

		if (curl) {

			// Set Headers and URL request
			curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:67.0) Gecko/20100101 Firefox/67.0");
			curl_easy_setopt(curl, CURLOPT_URL, "https://api.aeriagames.com/dialog/oauth?response_type=code&client_id=0ad0734dc5df644018b5fbfc8265ec6c05bb218dc&state=xyz&lang=es&Scope=scope_general,scope_billing");
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1L);
			curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");

			// Params
			string p = getParams();
			//cout << p << endl << endl;

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, p.c_str());

			res = curl_easy_perform(curl);

			char *url = NULL;
			curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
			if (url) {
				
				//cout << url << endl;

				// Extraemos el token de la URL
				string url_string = url;
				string token = url_string.substr(url_string.find("code=") + 5, url_string.size());
				
				cout << "-----------------------------------------------------------------" << endl;
				cout << token << endl;
				cout << "-----------------------------------------------------------------" << endl;

				cout << "GG!" << endl;

				string command = "GrandFantasia.exe EasyFun -a " + token + " -p xlwlogin";
				system(command.c_str());

			} else {
				cout << "Ups!" << endl;
			}

			curl_easy_cleanup(curl);
		}

		curl_global_cleanup();
	}
};



int main(int argc, char *argv[])
{
	cout << endl;
	cout << "+========================================================+" << endl;
	cout << "| GFAuth v 0.0.1 [ES]                                    |" << endl;
	cout << "+--------------------------------------------------------+" << endl;
	cout << "| By PRB [c] 2019                                        |" << endl;
	cout << "+========================================================+" << endl;
	cout << endl;
	cout << endl;


	if (argc <= 1) {
		cout << "Debes agregar 2 parametros al acceso directo, separados por espacios (user y pass)" << endl;
		system("pause");
		return 1;
	}

	string user = argv[1];
	string pass = argv[2];

	// Instanciamos la clase y procesamos los datos
	PRBAuth prb(user, pass);
	prb.sendForm();

	cout << endl;

	system("pause");
	return 0;

}
