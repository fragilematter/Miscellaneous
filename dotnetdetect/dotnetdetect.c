#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int netdetect(int);

int main(int argc, char* argv[]) {
  int i, netver;
  
  if (argc < 2) {
    printf("Usage: %s <code1> [code2]...\n", argv[0]);
    printf("\ncode\tversion\n11\tv1.1\n20\tv2.0\n30\tv3.0\n35\tv3.5\n41\tv4.0 client profile\n42\tv4.0 full profile\n");
    printf("\nReturn values\n1\tfound\n0\tnot found\n-1\tinvalid code\n");
  }
  else {
    for (i = 1; i < argc; i++) {
      netver = atoi(argv[i]);
      printf("%i\t%i\n", netver, netdetect(netver));
    }
  }
  
  return 0;
}

int netdetect(int version) {
  HKEY hkey;
  DWORD size, dt;
  LPBYTE read;
  const char* regstring;
  const char* regkey;
  int retval;

  size = (DWORD)sizeof(DWORD);
  read = 0;
  retval = 0;

  static const char* const netf11 = "Software\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322";
  static const char* const netf20 = "Software\\Microsoft\\NET Framework Setup\\NDP\\v2.0.50727";
  static const char* const netf30 = "Software\\Microsoft\\NET Framework Setup\\NDP\\v3.0\\Setup";
  static const char* const netf35 = "Software\\Microsoft\\NET Framework Setup\\NDP\\v3.5";
  static const char* const netf40c = "Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Client";
  static const char* const netf40f = "Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full";
  static const char* const key_normal = "Install";
  static const char* const key_special = "InstallSuccess";

  switch (version) {
    case 11:
      regstring = netf11;
      regkey = key_normal;
    
      break;
      
    case 20:
      regstring = netf20;
      regkey = key_normal;

      break;
      
    case 30:
      regstring = netf30;
      regkey = key_special;
    
      break;
    
    case 35:
      regstring = netf35;
      regkey = key_normal;

      break;
      
    case 41:
      regstring = netf40c;
      regkey = key_normal;

      break;
      
    case 42:
      regstring = netf40f;
      regkey = key_normal;

      break;
  
    default:
      return -1;
  }

  if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, regstring, 0, KEY_QUERY_VALUE, &hkey) == ERROR_SUCCESS) {
    if (RegQueryValueExA(hkey, regkey, NULL, &dt, (LPBYTE)&read, &size) == ERROR_SUCCESS) {
      if ((int)read == 1)
        retval = 1;
    }
    
    RegCloseKey(hkey);
  }

  return retval;
}
