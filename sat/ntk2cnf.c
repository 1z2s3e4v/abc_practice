#include <time.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "base/abc/abc.h"
#include "sat/bsat/satSolver.h"

// *************************************************
int
AddClause(lits, S)
veci lits;
sat_solver* S;
{
	lit* begin;
  
  begin = veci_begin(&lits);
  if (!sat_solver_addclause(S, begin, begin+veci_size(&lits))){
    return 0;
  }
	
	return 1;
}
// *************************************************
void ntk2cnf(ntk)
Abc_Ntk_t *ntk;
{
	int i, varA, varB, varC, j;
	Abc_Obj_t *node, *pi;
	int st;
	lit* begin;
	
	sat_solver *S; // declaration 
	veci lits; // declaration

	// << CNF construction >>

	S = sat_solver_new(); // create
	veci_new(&lits); // create

	Abc_NtkForEachObj(ntk, node, i){
		if (node->Type==ABC_OBJ_PI) continue;	// PI
		
		if (node->Type==ABC_OBJ_CONST1) {	// constant one
			varA = node->Id+1;
			
			veci_resize(&lits, 0); 
			veci_push(&lits, toLit(varA));	// initialize a clause	
		  st = AddClause(lits, S);
		  if (st==0) {printf("UNSAT"); break;}	
		}
		
		if (node->Type==ABC_OBJ_PO) {		// primary output
			varA = node->Id+1;
			varB = Abc_ObjFanin0(node)->Id+1;
			if (node->fCompl0){	// A = B'
				// B A 0
				veci_resize(&lits, 0);
				veci_push(&lits, toLit(varB));
				veci_push(&lits, toLit(varA));
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
	      	
				// -B -A 0
				veci_resize(&lits, 0);
				veci_push(&lits, lit_neg(toLit(varB)));
				veci_push(&lits, lit_neg(toLit(varA)));			
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
			}else{	// A = B
				// B -A 0
				veci_resize(&lits, 0);
				veci_push(&lits, toLit(varB));
				veci_push(&lits, lit_neg(toLit(varA)));			
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
	      	
				// -B A 0
				veci_resize(&lits, 0);
				veci_push(&lits, lit_neg(toLit(varB)));		
				veci_push(&lits, toLit(varA));			
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
			} 
		}
		
		if (node->Type==ABC_OBJ_NODE) {	// internal node
			varA = node->Id+1;
			varB = Abc_ObjFanin0(node)->Id+1;
			varC = Abc_ObjFanin1(node)->Id+1;
			
			if (node->fCompl0 && node->fCompl1)	// A = B' & C'
			{
				// B C A 0
				veci_resize(&lits, 0);
				veci_push(&lits, toLit(varB));
				veci_push(&lits, toLit(varC));
				veci_push(&lits, toLit(varA));
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
				
				// -B -A 0
				veci_resize(&lits, 0);
				veci_push(&lits, lit_neg(toLit(varB)));
				veci_push(&lits, lit_neg(toLit(varA)));			
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
	      			
				// -C -A 0
				veci_resize(&lits, 0);
				veci_push(&lits, lit_neg(toLit(varC)));
				veci_push(&lits, lit_neg(toLit(varA)));	
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
			}
			else if (!node->fCompl0 && node->fCompl1) // A = B & C'
			{
				// -B C A 0
				veci_resize(&lits, 0);
				veci_push(&lits, lit_neg(toLit(varB)));
				veci_push(&lits, toLit(varC));	
				veci_push(&lits, toLit(varA));			
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
				
				// B -A 0
				veci_resize(&lits, 0);
				veci_push(&lits, toLit(varB));
				veci_push(&lits, lit_neg(toLit(varA)));			
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
	      			
				// -C -A 0
				veci_resize(&lits, 0);
				veci_push(&lits, lit_neg(toLit(varC)));	
				veci_push(&lits, lit_neg(toLit(varA)));		
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
			}
			else if (node->fCompl0 && !node->fCompl1) // A = B' & C
			{
				// B -C A 0
				veci_resize(&lits, 0);
				veci_push(&lits, toLit(varB));	
				veci_push(&lits, lit_neg(toLit(varC)));
				veci_push(&lits, toLit(varA));			
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
				
				// -B -A 0
				veci_resize(&lits, 0);
				veci_push(&lits, lit_neg(toLit(varB)));		
				veci_push(&lits, lit_neg(toLit(varA)));			
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
	      			
				// C -A 0
				veci_resize(&lits, 0);
				veci_push(&lits, toLit(varC));
				veci_push(&lits, lit_neg(toLit(varA)));		
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
			}
			else																			// A = B & C
			{
				// -B -C A 0
				veci_resize(&lits, 0);
				veci_push(&lits, lit_neg(toLit(varB)));
				veci_push(&lits, lit_neg(toLit(varC)));
				veci_push(&lits, toLit(varA));			
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
				
				// B -A 0
				veci_resize(&lits, 0);
				veci_push(&lits, toLit(varB));
				veci_push(&lits, lit_neg(toLit(varA)));			
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
	      			
				// C -A 0
				veci_resize(&lits, 0);
				veci_push(&lits, toLit(varC));
				veci_push(&lits, lit_neg(toLit(varA)));		
	      st = AddClause(lits, S);
	      if (st==0) {printf("UNSAT"); break;}
			}
		}
	}
	
	
	// << Constraint, optional>
	node = Abc_NtkPi(ntk, 0); // first PI
	veci_resize(&lits, 0);
	veci_push(&lits, toLit(node->Id+1)); // set first Pi to be 1
	st = AddClause(lits, S);
	if (st==0) {printf("UNSAT");}
/*
	// << Solving >>
	st = sat_solver_solve(S, 0, 0, (ABC_INT64_T)0, (ABC_INT64_T)0, (ABC_INT64_T)0, (ABC_INT64_T)0);
	printf("status %d\n", st);
	
	// << Show results >>
	Abc_NtkForEachPi(ntk, node, i){
		printf("%d %d, ", node->Id, sat_solver_var_value(S, node->Id+1)); 
	}
	printf("\n");
*/	
	
	// << incremental sat solving >>
	// check if each pi can be 1
	Abc_NtkForEachPi(ntk, node, i){
		veci_resize(&lits, 0);
		veci_push(&lits, toLit(node->Id+1));
		begin = veci_begin(&lits);
		st = sat_solver_solve(S, begin, begin+veci_size(&lits), (ABC_INT64_T)0, (ABC_INT64_T)0, (ABC_INT64_T)0, (ABC_INT64_T)0); 
		if (st==-1) printf("PI %d cannot be 1\n", node->Id);
		else{
			Abc_NtkForEachPi(ntk, pi, j){
				printf("%d %d, ", pi->Id, sat_solver_var_value(S, pi->Id+1)); 
			}
			printf("\n");	
		}
	}
	

	veci_delete(&lits); // delete	
	sat_solver_delete(S); // delete

}
