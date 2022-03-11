#include <time.h>
#include <stdio.h>
#include <string.h>
#include "base/abc/abc.h"

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

#if defined(ABC_NAMESPACE)
namespace ABC_NAMESPACE
{
#elif defined(__cplusplus)
extern "C"
{
#endif

// procedures to start and stop the ABC framework
// (should be called before and after the ABC procedures are called)
void   Abc_Start();
void   Abc_Stop();

// procedures to get the ABC framework and execute commands in it
typedef struct Abc_Frame_t_ Abc_Frame_t;

Abc_Frame_t * Abc_FrameGetGlobalFrame();
int    Cmd_CommandExecute( Abc_Frame_t * pAbc, const char * sCommand );

Abc_Ntk_t *Io_ReadBlifAsAig(char*, int);

#if defined(ABC_NAMESPACE)
}
using namespace ABC_NAMESPACE;
#elif defined(__cplusplus)
}
#endif

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

//***********************************************************
void PrintEachObj(Abc_Ntk_t *ntk) {
	Abc_Obj_t *node, *fi;
	int i, j;
	
	printf("<< Print Each Obj- >>\n");
	printf(" ID       Name  Type  Levle\n");
	printf("--------------------\n");
	Abc_NtkForEachObj(ntk, node, i){
		printf("%3d %10s %2d %2d\n", node->Id, Abc_ObjName(node), node->Type, node->Level);
	
		Abc_ObjForEachFanin(node, fi, j){
			printf("  %10s %d\n", Abc_ObjName(fi), Abc_ObjFaninC(node, j));
		}
	}
	printf("<< ----- End ----- >>\n");                          
}

//***********************************************************
int main(int argc, char **argv)
{
	char circuit[100];			// input circuit name.
	Abc_Ntk_t *ntk;

	printf("Process %s\n", argv[argc-1]);
	
	// << Setup ABC >>
	Abc_Start();
	
	// << Read blif file >>
	strcpy(circuit, argv[argc-1]);
	if (!(ntk = Io_ReadBlifAsAig(circuit, 1))) return 1; 

	PrintEachObj(ntk);   

	Abc_NtkDelete(ntk);

	// << End ABC >>
	Abc_Stop();
	
	return 1;
}
