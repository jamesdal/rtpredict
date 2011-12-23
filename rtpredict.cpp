//James Dalgleish
//C++ retention time predictor-- RTPredict
//basic file i/o may resemble tutorial code on: http://www.cprogramming.com/tutorial/c/lesson14.html
//hrlog 11:46-12:00, 1:16-1:48
/*
#include<iostream>
#include<stdio.h>

#include<string.h>
#include<cctype>
#include<algorithm>
using namespace std;
using std::transform;
used some info*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
using std::ctype;
using std::string;
using std::transform;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cout;
char ** argvptr;  //knowledge of copying argv from http://stackoverflow.com/questions/4057961/how-to-access-argv-from-outside-the-main-function

bool scanargv(char* parameter)
{
    int i = 1;
    while (argvptr[i] != NULL)
    {
        if (strcmp(parameter,argvptr[i])==0)
        {
            return true;
        }
        else
        {
            return false;
        }
        i++;
    }
}
int getargvindex(char* parameter)
{
    int i = 1;
    while (argvptr[i] != NULL)
    {
        if (strcmp(parameter,argvptr[i])==0)
        {
            return i;
        }

        i++;
    }
}
int main (int argc, char *argv[])
{
    argvptr = argv;
    if (scanargv("-t"))
    {

        std::string filenamewithext = argv[getargvindex("-t")+1];
        std::string ext = filenamewithext.substr(filenamewithext.rfind("."),1024);
        std::transform(ext.begin(), ext.end(),  ext.begin(), ::tolower);
        /*if (ext.compare("mzxml"))  //rfind will give the extension here
        {
            printf("true");
        }
        else
        {
            printf("false");
        }*/
        if (ext.compare("csv"))
        {

            string line;  //some code may resemble samples on http://www.cplusplus.com/doc/tutorial/files/
            ifstream csvfile;
            csvfile.open (argv[getargvindex("-t")+1]);
             char* filenamewithextdotarff;
             char* filename = argv[getargvindex("-t")+1];
             strcpy(filenamewithextdotarff,argv[getargvindex("-t")+1]);
             strcat (filenamewithextdotarff,".arff");
            ofstream fromCSV(filenamewithextdotarff);
//            arffInput.open() //weka ARFF specification found here
            fromCSV  << "@RELATION ilist\n\n";
            fromCSV  << "@ATTRIBUTE mz  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE charge  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE intensity  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE A  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE R  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE N  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE D  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE B  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE C  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE E  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE Q  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE Z  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE G  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE H  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE I  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE L  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE K  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE M  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE F  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE P  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE S  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE T  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE W  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE Y  NUMERIC\n";
            fromCSV  << "@ATTRIBUTE V  NUMERIC\n";//selenocysteine and pyrrolysine removed, add hydrophobicity attribute once calculated
            fromCSV  << "@ATTRIBUTE rt  NUMERIC\n\n";
            fromCSV  << "@DATA\n";
            while (csvfile.good())
            {
                getline(csvfile,line);
                fromCSV << line << endl;
                cout << line << endl;
            }


            fromCSV.close();

        }
        else if (ext.compare("pepxml"))
        {
            printf("pepxml format is not yet supported in the current version of rtpredict");
            return 0;
        }
        else if (ext.compare("mzxml"))
        {
            printf("mzxml format is not yet supported in the current version of rtpredict");
            return 0;
        }
        else if (ext.compare("mzml"))
        {
            printf("mzml format is not yet supported in the current version of rtpredict");
            return 0;

        }
    }
    else
    {
        printf("usage RTPredict -t TRAININGFILE.EXT \n  Currently supported formats include: \n csv");

        return 0;
    }
//SCANARGS IF STATEMENT GOES HERE
//system("java -classpath ./weka.jar weka.filters.supervised.instance.StratifiedRemoveFolds -i fromCSV.arff -o Train.arff -c last -N 4 -F 1 -V");
    //system("java -classpath ./weka.jar weka.filters.supervised.instance.StratifiedRemoveFolds -i fromCSV.arff -o Test.arff -c last -N 4 -F 1");

    //system("java -classpath ./weka.jar -Xmx512m weka.classifiers.functions.SMOreg -t fromCSV.arff -T fromCSV.arff -p 0 -C 1 -N 2 >> results.txt");
    system("java -classpath ./weka.jar -Xmx512m weka.classifiers.rules.M5Rules -M 4.0 -t fromCSV.arff -o -split-percentage 1 > wekaoutput.txt");
    //this will run all algorithms... some sort of limiting measure needs to be done, split validation to select the correct one before a real analysis is to take place.
    system("java -classpath ./weka.jar -Xmx512m weka.classifiers.meta.MultiScheme -X 0 -S 1 -B \"weka.classifiers.rules.M5Rules -M 4.0\" -B \"weka.classifiers.trees.REPTree -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.trees.M5P -M 4.0\" -B \"weka.classifiers.lazy.LWL -U 0 -K -1 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\" -W weka.classifiers.trees.DecisionStump\" -B \"weka.classifiers.lazy.KStar -B 20 -M a\" -B \"weka.classifiers.lazy.IBk -K 1 -W 0 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\"\" -B \"weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a\" -B \"weka.classifiers.functions.SMOreg -C 1.0 -N 0 -I \"weka.classifiers.functions.supportVector.RegSMOImproved -L 0.001 -W 1 -P 1.0E-12 -T 0.001 -V\" -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.functions.SimpleLinearRegression \" -B \"weka.classifiers.rules.ZeroR \" -B \"weka.classifiers.meta.Bagging -P 100 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.functions.GaussianProcesses -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.meta.RandomSubSpace -P 0.5 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.meta.CVParameterSelection -X 10 -S 1 -W weka.classifiers.rules.ZeroR\" -B \"weka.classifiers.meta.RegressionByDiscretization -B 10 -K 0 -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.Stacking -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.ZeroR \"\" -B \"weka.classifiers.meta.Vote -S 1 -B \"weka.classifiers.rules.ZeroR \" -R AVG\" -B \"weka.classifiers.rules.DecisionTable -X 1 -S \"weka.attributeSelection.BestFirst -D 1 -N 5\"\" -B \"weka.classifiers.trees.DecisionStump \" -B \"weka.classifiers.meta.AttributeSelectedClassifier -E \"weka.attributeSelection.CfsSubsetEval \" -S \"weka.attributeSelection.BestFirst -D 1 -N 5\" -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -t fromCSV.arff -split-percentage 1 -p 0 > wekaoutput.txt");

        const char* alglabel = argv[getargvindex("-a")+1];
        const char* algparams = "weka.classifiers.meta.MultiScheme -X 0 -S 1 -B \"weka.classifiers.rules.M5Rules -M 4.0\" -B \"weka.classifiers.trees.REPTree -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.trees.M5P -M 4.0\" -B \"weka.classifiers.lazy.LWL -U 0 -K -1 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\" -W weka.classifiers.trees.DecisionStump\" -B \"weka.classifiers.lazy.KStar -B 20 -M a\" -B \"weka.classifiers.lazy.IBk -K 1 -W 0 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\"\" -B \"weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a\" -B \"weka.classifiers.functions.SMOreg -C 1.0 -N 0 -I \"weka.classifiers.functions.supportVector.RegSMOImproved -L 0.001 -W 1 -P 1.0E-12 -T 0.001 -V\" -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.functions.SimpleLinearRegression \" -B \"weka.classifiers.rules.ZeroR \" -B \"weka.classifiers.meta.Bagging -P 100 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.functions.GaussianProcesses -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.meta.RandomSubSpace -P 0.5 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.meta.CVParameterSelection -X 10 -S 1 -W weka.classifiers.rules.ZeroR\" -B \"weka.classifiers.meta.RegressionByDiscretization -B 10 -K 0 -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.Stacking -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.ZeroR \"\" -B \"weka.classifiers.meta.Vote -S 1 -B \"weka.classifiers.rules.ZeroR \" -R AVG\" -B \"weka.classifiers.rules.DecisionTable -X 1 -S \"weka.attributeSelection.BestFirst -D 1 -N 5\"\" -B \"weka.classifiers.trees.DecisionStump \" -B \"weka.classifiers.meta.AttributeSelectedClassifier -E \"weka.attributeSelection.CfsSubsetEval \" -S \"weka.attributeSelection.BestFirst -D 1 -N 5\" -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -t fromCSV.arff -split-percentage 1";
    if (strcmp(alglabel,"gaussian"))
{
    const char* algparams = "weka.classifiers.functions.GaussianProcesses -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"";
}
else if (strcmp(alglabel,"linreg"))
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}
else if (strcmp(alglabel,"multipercept"))
{
    const char* algparams = "weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a";
}
/*else if (strcmp(alglabel,"linreg")
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}
else if (strcmp(alglabel,"linreg")
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}
else if (strcmp(alglabel,"linreg")
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}
else if (strcmp(alglabel,"linreg")
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}
else if (strcmp(alglabel,"linreg")
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}
else if (strcmp(alglabel,"linreg")
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}
else if (strcmp(alglabel,"linreg")
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}
else if (strcmp(alglabel,"linreg")
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}
else if (strcmp(alglabel,"linreg")
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}
else if (strcmp(alglabel,"linreg")
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}
else if (strcmp(alglabel,"linreg")
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}
else if (strcmp(alglabel,"linreg")
{
    const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
}

/*    else if (strcmp(alglabel,"linreg")
             {
                const char* algparams = "weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8";
             }*/
else
{

}
//format for system call: java -classpath ./weka.jar -Xmx512m <algparams> -t <filenamewithext>.arff > <filenamewithext>.txt
//strcat reference code: http://www.cplusplus.com/reference/clibrary/cstring/strcat/
  char* syscall;
  strcpy (syscall,"java -classpath ./weka.jar -Xmx512m ");
  strcat (syscall,algparams);
  strcat (syscall," -t ");
  strcat (syscall,filenamewithextdotarff);
  strcat (syscall,".arff - p 0 > ");
  strcat (syscall,argv[getargvindex("-t")+1]);
  strcat (syscall,".txt");
  system(syscall);
return 0;
}
