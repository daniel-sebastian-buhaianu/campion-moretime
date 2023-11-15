#include <fstream>
#define MAX_CLIENTI 10000
using namespace std;
struct Client { int nrCont, valoareFond; };
bool esteClientPremium(int);
int main()
{
  Client client[MAX_CLIENTI];
  int suma[MAX_CLIENTI], rest[MAX_CLIENTI];
  int nrClienti, nrClientiPremium, i;
	ifstream fin("moretime.in");
	fin >> nrClienti;
	for (nrClientiPremium = i = 0; i < nrClienti; i++)
	{
    int nrCont, valoareFond;
    fin >> nrCont >> valoareFond;
    if (esteClientPremium(nrCont))
    {
      client[nrClientiPremium].nrCont = nrCont;
      client[nrClientiPremium].valoareFond = valoareFond;
      nrClientiPremium++;
    }
	}
	fin.close();
	ofstream fout("moretime.out");
  fout << nrClientiPremium << '\n';
  suma[0] = client[0].valoareFond;
  rest[0] = suma[0] % nrClientiPremium;
  if (rest[0] == 0)
    fout << 1 << '\n' << client[0].nrCont;
  else
  {
    int j;
    bool amGasitSolutie = false;
    for (i = 1; i < nrClientiPremium && !amGasitSolutie; i++)
    {
      suma[i] = suma[i-1] + client[i].valoareFond;
      rest[i] = suma[i] % nrClientiPremium;
      if (rest[i] == 0)
      {
        amGasitSolutie = true;
        fout << i+1 << '\n';
        for (j = 0; j <= i; j++)
          fout << client[j].nrCont << ' ';
      }
    }
    for (i = 0; !amGasitSolutie && i < nrClientiPremium-1; i++)
    {
      for (j = i+1; j < nrClientiPremium; j++)
        if (rest[i] == rest[j])
        {
          amGasitSolutie = true;
          break;
        }
      if (amGasitSolutie)
      {
        fout << j-i << '\n';
        for (i = i+1; i <= j; i++)
          fout << client[i].nrCont << ' ';
      }
    }
  }
	fout.close();
	return 0;
}
bool esteClientPremium(int nrCont)
{
  int ultimaCifra = nrCont % 10;
  while (nrCont > 9) nrCont /= 10;
  int primaCifra = nrCont;
  return ultimaCifra == primaCifra;
}
