#include <iostream>
using namespace std ;



enum enDifficultyLevel {eEasy = 1 , eHard = 2 , eMix = 3 } ;

enum enOperationType { eAdd = 1 , eSub = 2 , eMul = 3 , eDiv = 4 } ;

enum enPassFail { ePass = 1 , eFail = 2 } ;


struct stRoundInfo {
	short rounds = 0 ;
	enDifficultyLevel level ;
	enOperationType Op ;
	short rand1 = 0 ;
	short rand2 = 0 ;
	short userAnswer = 0 ;
	enPassFail passFail ;
} ;

struct stGameResults {
	enPassFail passFail ;
	short gameRounds = 0 ;
	enDifficultyLevel level ;
	enOperationType Op ;
	short rightAnswerTimes = 0 ;
	short wrongAnswerTimes = 0 ;
} ;




short UserInputs(string Message , short from , short to){
	short number = 0 ;
	
	do{
		cout << Message ;
		cin >> number ;
	}while(number < from && number > to) ;
	
	return number ;
}



short RandomNumber(short from , short to){
	return rand() % (to - from + 1) + from ;
}


enDifficultyLevel CheckDifficulty(short number){
	switch(number){
		case 1 :
		return enDifficultyLevel :: eEasy ;
		
		case 2 :
		return enDifficultyLevel :: eHard ;
		
		case 3 :
		return enDifficultyLevel :: eMix ;
	}
}



enOperationType CheckOperation(short number){
	switch(number){
		case 1 :
		return enOperationType :: eAdd ;
		
		case 2 :
		return enOperationType :: eSub ;
		
		case 3 :
		return enOperationType :: eMul ;
		
		case 4 :
		return enOperationType :: eDiv ;
	}
}



string DifficultyName(enDifficultyLevel level){
	string arrLevelName[3] = { "Easy" , "Hard" , "Mix" } ;
	
	return arrLevelName[level - 1] ;
}


string OperationName(enOperationType Op){
	string arrOperationName[4] = { "Add" , "Substract" , "Multiply" , "Divide" } ;
	
	return arrOperationName[Op - 1] ;
}



string PassFailName(enPassFail passFail){
	string arrPassFailName[2] = { "Pass" , "Fail" } ;
	
	return arrPassFailName[passFail - 1] ;
}




void CreateEquationDifficulty(stRoundInfo &roundInfo){
	switch(roundInfo.level){
		
		case enDifficultyLevel :: eEasy :
		roundInfo.rand1 = RandomNumber(1 , 10) ;
		roundInfo.rand2 = RandomNumber(1 , 10) ;
		break ;
		
		case enDifficultyLevel :: eHard :
		roundInfo.rand1 = RandomNumber(50 , 100) ;
		roundInfo.rand2 = RandomNumber(50 , 100) ;
		break ;
		
		case enDifficultyLevel :: eMix :
		roundInfo.rand1 = RandomNumber(1 , 100) ;
		roundInfo.rand2 = RandomNumber(1 , 100) ;
		break ;
	}
}



short ReadUserAnswer(stRoundInfo roundInfo , short howManyRounds){
	int answer = 0 ;
	
	cout << "\nQuestion {" << roundInfo.rounds << "/" << howManyRounds << "}\n" ;
	
	switch(roundInfo.Op){
		
		case enOperationType :: eAdd :
		cout << "\t" << roundInfo.rand1 << "\n" ;
		cout << "\t" << roundInfo.rand2 << "  +" ;
		break ;
		
		case enOperationType :: eSub :
		cout << "\t" << roundInfo.rand1 << "\n" ;
		cout << "\t" << roundInfo.rand2 << "  -" ;
		break ;
		
		case enOperationType :: eMul :
		cout << "\t" << roundInfo.rand1 << "\n" ;
		cout << "\t" << roundInfo.rand2 << "  *" ;
		break ;
		
		case enOperationType :: eDiv :
		cout << "\t" << roundInfo.rand1 << "\n" ;
		cout << "\t" << roundInfo.rand2 << "  /" ;
		break ;
	}
	cout << "\n_______________\n" ;
	cin >> answer ;
	
	return answer ;
}



short RightSolution(stRoundInfo roundInfo){
	switch(roundInfo.Op){
		
		case enOperationType :: eAdd :
		return roundInfo.rand1 + roundInfo.rand2 ;
		break ;
		
		case enOperationType :: eSub :
		return roundInfo.rand1 - roundInfo.rand2 ;
		break ;
		
		case enOperationType :: eMul :
		return roundInfo.rand1 * roundInfo.rand2 ;
		break ;
		
		case enOperationType :: eDiv :
		return roundInfo.rand1 / roundInfo.rand2 ;
		break ;
	}
}



void PrintRoundInfo(enPassFail passFail ,  short rightAnswer){
	
	if(passFail == enPassFail :: ePass){
		cout << "Right answer :)\n\n\n" ;
	}
	else{
		cout << "Wrong answer :(" ;
		cout << "\nThe right answer is " << rightAnswer << "\n\n" << endl ;
	}
}



enPassFail FinalGameResult(short right , short wrong){
	if(right > wrong){
		return enPassFail :: ePass ;
	}
	else{
		return enPassFail :: eFail ;
	}
}



string FaceResult(enPassFail passFail){
	if(passFail == enPassFail :: ePass){
		return ":-)" ;
	}
	else{
		return ":-(" ;
	}
}



stGameResults FillGameResults(short totalRoundsNumber , enDifficultyLevel level , enOperationType Op , short rightAnswerTimes , short wrongAnswerTimes){
	
	stGameResults gameResults ;
	
	gameResults.passFail = FinalGameResult(rightAnswerTimes , wrongAnswerTimes) ;
	
	gameResults.gameRounds = totalRoundsNumber ;
	
	gameResults.level = level ;
	
	gameResults.Op = Op ;
	
	gameResults.rightAnswerTimes = rightAnswerTimes ;
	
	gameResults.wrongAnswerTimes = wrongAnswerTimes ;
	
	return gameResults ;
}




stGameResults PlayGame(short howManyRounds){
	stRoundInfo roundInfo ;
	
	short rightAnswer = 0 , rightAnswerTimes = 0 , wrongAnswerTimes = 0 ;
	
	roundInfo.level = CheckDifficulty(UserInputs("\nEnterdifficulty level ? [1]: Easy , [2]: Hard , [3]: Mix : " , 1 , 3)) ;
		
		roundInfo.Op = CheckOperation(UserInputs("\nEnter operation type ? [1]: Add , [2]: Substract , [3]: Multiply , [4]: Divide : ", 1 , 4)) ;
		
	for(short roundNumber = 1 ; roundNumber <= howManyRounds ; roundNumber++){
		
		roundInfo.rounds = roundNumber ;
		
		CreateEquationDifficulty(roundInfo) ;
		
		roundInfo.userAnswer = ReadUserAnswer(roundInfo , howManyRounds) ;
		
		rightAnswer = RightSolution(roundInfo) ;
		
		if(roundInfo.userAnswer == rightAnswer){
			rightAnswerTimes++ ;
			roundInfo.passFail = enPassFail :: ePass ; }
		else{
			wrongAnswerTimes++ ;
			roundInfo.passFail = enPassFail :: eFail ; } ;
			
			PrintRoundInfo(roundInfo.passFail , rightAnswer) ;
	}
	
	
	return FillGameResults (howManyRounds , roundInfo.level , roundInfo.Op , rightAnswerTimes , wrongAnswerTimes) ;
}



void ShowGameResults(stGameResults gameResults){
	
	cout << "\n\n____________________________\n" ;
	cout << "Final Result Is : " << PassFailName(gameResults.passFail) << " " << FaceResult(gameResults.passFail) ;
	 cout << "\n______________________________\n" ;
	 
	  
	   cout << "\nNumber Of Questions : " << gameResults.gameRounds ;
	   
	   cout << "\nQuestion Level : " << DifficultyName(gameResults.level) ;
	   
	   cout << "\nOperation Type : " << OperationName(gameResults.Op) ;
	   
	   cout << "\nNumber Of Right Answers : " << gameResults.rightAnswerTimes ;
	   
	   cout << "\nNumber Of Wrong Answers : " << gameResults.wrongAnswerTimes ;
	   
}



void StartGame(){
	char playAgain = 'y' ;
	
	do{
		system("cls") ;
		stGameResults gameResults = PlayGame(UserInputs("Enter how many rounds : " , 1 , 10)) ;
		
		ShowGameResults(gameResults) ;
		
		cout << "\n\nDo you want to play again Y/N ? " ;
		cin >> playAgain ;
	}while(playAgain == 'y' || playAgain == 'Y') ;
}



int main(){
	srand((unsigned)time(NULL)) ;
	
	StartGame() ;
	
	return 0 ;
}