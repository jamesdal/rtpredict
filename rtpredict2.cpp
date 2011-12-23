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
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;
using std::ctype;
using std::string;
using std::transform;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cout;
char ** argvptr;  //knowledge of copying argv from http://stackoverflow.com/questions/4057961/how-traino-access-argv-from-outside-trainhe-main-function
std::string modelname;
std::string wsyscall = "";

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
/*int countAA(const char* seq, int residue)
{
    int count = 0;
    int i = 0;
    while (seq[i] != '\0' || i == 0)
    {
        if(seq[i]==residue)
        {
            count++;
            i++;
        }
        else
        {
            i++;
        }
    }
}*/
int countAA(const char* seq, int residue)
{
    int count = 0;
    int i = 0;
    std::string seq_str = seq;
//    std::string residue_str = residue;
    while(i < seq_str.length())
    {
//        printf("the length of the string is %d",seq_str.length());
  //      cout << (char)seq_str.at(9);
            if (seq_str.at(i) == residue)
            {
                count++;
                i++;
            }
            else
            {
                i++;
            }
    }

    return count;
}
int main (int argc, char *argv[])
{
    argvptr = argv;
    std::string filenamewithextdotarff;
    if (scanargv("-train"))
    {

        std::string filenamewithext = argv[getargvindex("-train")+1];
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
            std::string field = "";
            string line;  //some code may resemble samples on http://www.cplusplus.com/doc/tutorial/files/
            ifstream csvfile;
            csvfile.open (argv[getargvindex("-train")+1]);
            std::string filenamewithextdotarff;
            std::string filename = argv[getargvindex("-train")+1];
            std::copy( filename.begin(), filename.end(), back_inserter( filenamewithextdotarff ) );
            filenamewithextdotarff.insert(filenamewithextdotarff.end(), std::string(".arff").begin(), std::string(".arff").end());
            ofstream fromCSV(filenamewithextdotarff.c_str());
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
            //first line contains the differing fields, so scanning will take place here
            getline(csvfile,line);

            while (csvfile.good())
            {  //input file format seq mz intensity charge rt\
                getline(csvfile,line);//idea from post:  http://www.cplusplus.com/forum/general/17771/
                istringstream littlestream (line,istringstream::in);
                getline(littlestream,field,',');
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
        printf("usage rtpredict -train TRAININGFILE.EXT \n  Currently supported formats include: \n csv");
        return 0;
    }
//SCANARGS IF STATEMENT GOES HERE
//system("java -classpath ./weka.jar weka.filters.supervised.instance.StratifiedRemoveFolds -i fromCSV.arff -o Train.arff -c last -N 4 -F 1 -V");
    //system("java -classpath ./weka.jar weka.filters.supervised.instance.StratifiedRemoveFolds -i fromCSV.arff -o Test.arff -c last -N 4 -F 1");

    //system("java -classpath ./weka.jar -Xmx512m weka.classifiers.functions.SMOreg -train fromCSV.arff -train fromCSV.arff -p 0 -C 1 -N 2 >> results.txt");
    system("java -classpath ./weka.jar -Xmx512m weka.classifiers.rules.M5Rules -M 4.0 -train fromCSV.arff -o -split-percentage 1 > wekaoutput.txt");
    //this will run all algorithms... some sort of limiting measure needs to be done, split validation to select the correct one before a real analysis is to take place.
    system("java -classpath ./weka.jar -Xmx512m weka.classifiers.meta.MultiScheme -X 0 -S 1 -B \"weka.classifiers.rules.M5Rules -M 4.0\" -B \"weka.classifiers.trees.REPTree -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.trees.M5P -M 4.0\" -B \"weka.classifiers.lazy.LWL -U 0 -K -1 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\" -W weka.classifiers.trees.DecisionStump\" -B \"weka.classifiers.lazy.KStar -B 20 -M a\" -B \"weka.classifiers.lazy.IBk -K 1 -W 0 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\"\" -B \"weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a\" -B \"weka.classifiers.functions.SMOreg -C 1.0 -N 0 -I \"weka.classifiers.functions.supportVector.RegSMOImproved -L 0.001 -W 1 -P 1.0E-12 -train 0.001 -V\" -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.functions.SimpleLinearRegression \" -B \"weka.classifiers.rules.ZeroR \" -B \"weka.classifiers.meta.Bagging -P 100 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.functions.GaussianProcesses -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.meta.RandomSubSpace -P 0.5 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.meta.CVParameterSelection -X 10 -S 1 -W weka.classifiers.rules.ZeroR\" -B \"weka.classifiers.meta.RegressionByDiscretization -B 10 -K 0 -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.Stacking -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.ZeroR \"\" -B \"weka.classifiers.meta.Vote -S 1 -B \"weka.classifiers.rules.ZeroR \" -R AVG\" -B \"weka.classifiers.rules.DecisionTable -X 1 -S \"weka.attributeSelection.BestFirst -D 1 -N 5\"\" -B \"weka.classifiers.trees.DecisionStump \" -B \"weka.classifiers.meta.AttributeSelectedClassifier -E \"weka.attributeSelection.CfsSubsetEval \" -S \"weka.attributeSelection.BestFirst -D 1 -N 5\" -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -train fromCSV.arff -split-percentage 1 -p 0 > wekaoutput.txt");

    const char* alglabel = argv[getargvindex("-a")+1];
    const char* algorithm = "weka.classifiers.meta.MultiScheme";
    const char* options = " -X 0 -S 1 -B \"weka.classifiers.rules.M5Rules -M 4.0\" -B \"weka.classifiers.trees.REPTree -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.trees.M5P -M 4.0\" -B \"weka.classifiers.lazy.LWL -U 0 -K -1 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\" -W weka.classifiers.trees.DecisionStump\" -B \"weka.classifiers.lazy.KStar -B 20 -M a\" -B \"weka.classifiers.lazy.IBk -K 1 -W 0 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\"\" -B \"weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a\" -B \"weka.classifiers.functions.SMOreg -C 1.0 -N 0 -I \"weka.classifiers.functions.supportVector.RegSMOImproved -L 0.001 -W 1 -P 1.0E-12 -train 0.001 -V\" -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.functions.SimpleLinearRegression \" -B \"weka.classifiers.rules.ZeroR \" -B \"weka.classifiers.meta.Bagging -P 100 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.functions.GaussianProcesses -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.meta.RandomSubSpace -P 0.5 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.meta.CVParameterSelection -X 10 -S 1 -W weka.classifiers.rules.ZeroR\" -B \"weka.classifiers.meta.RegressionByDiscretization -B 10 -K 0 -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.Stacking -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.ZeroR \"\" -B \"weka.classifiers.meta.Vote -S 1 -B \"weka.classifiers.rules.ZeroR \" -R AVG\" -B \"weka.classifiers.rules.DecisionTable -X 1 -S \"weka.attributeSelection.BestFirst -D 1 -N 5\"\" -B \"weka.classifiers.trees.DecisionStump \" -B \"weka.classifiers.meta.AttributeSelectedClassifier -E \"weka.attributeSelection.CfsSubsetEval \" -S \"weka.attributeSelection.BestFirst -D 1 -N 5\" -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -train fromCSV.arff -split-percentage 1";
    if (strcmp(alglabel,"gaussian"))
    {
        algorithm = "weka.classifiers.functions.GaussianProcesses";
        options = " -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"";
    }
    if (strcmp(alglabel,"best")){}//this is the default, no explicit declaration is therefore needed here
    else if (strcmp(alglabel,"linreg"))
    {
        algorithm = "weka.classifiers.functions.LinearRegression";
        options = " -S 0 -R 1.0E-8";
    }
    else if (strcmp(alglabel,"multipercept"))
    {
        algorithm = "weka.classifiers.functions.MultilayerPerceptron";
        options = "const char* algoptions";
        options = " -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a\"";
    }
    else if (strcmp(alglabel,"simplelinreg"))
    {
        algorithm = "weka.classifiers.functions.SimpleLinearRegression";
        options = "";
    }
    else if (strcmp(alglabel,"kstar"))
    {
        algorithm = "weka.classifiers.lazy.KStar";
        options = " -B 20 -M a";
    }
    else if (strcmp(alglabel,"lwl"))
    {
        algorithm = "weka.classifiers.lazy.LWL";
        options = " -U 0 -K -1 -A \\\"weka.core.neighboursearch.LinearNNSearch -A \"weka.core.EuclideanDistance -R first-last\\\"\" -W weka.classifiers.trees.DecisionStump";
    }
    else if (strcmp(alglabel,"additive"))
    {
        algorithm = "weka.classifiers.meta.AdditiveRegression";
        options = " -S 1.0 -I 10 -W weka.classifiers.trees.DecisionStump";
    }
    else if (strcmp(alglabel,"attributeselected"))
    {
        algorithm = "weka.classifiers.meta.AttributeSelectedClassifier";
        options = " -E \"weka.attributeSelection.CfsSubsetEval \" -S \"weka.attributeSelection.BestFirst -D 1 -N 5\" -W weka.classifiers.meta.MultiScheme -- -X 0 -S 1 -B \"weka.classifiers.functions.GaussianProcesses -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.functions.LinearRegression -S 0 -R 1.0E-8\" -B \"weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a\" -B \"weka.classifiers.functions.SimpleLinearRegression \" -B \"weka.classifiers.functions.SMOreg -C 1.0 -N 0 -I \"weka.classifiers.functions.supportVector.RegSMOImproved -L 0.001 -W 1 -P 1.0E-12 -train 0.001 -V\" -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.lazy.IBk -K 1 -W 0 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\"\" -B \"weka.classifiers.lazy.KStar -B 20 -M a\" -B \"weka.classifiers.lazy.LWL -U 0 -K -1 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\" -W weka.classifiers.trees.DecisionStump\" -B \"weka.classifiers.meta.AdditiveRegression -S 1.0 -I 10 -W weka.classifiers.trees.DecisionStump\" -B \"weka.classifiers.meta.AttributeSelectedClassifier -E \"weka.attributeSelection.CfsSubsetEval \" -S \"weka.attributeSelection.BestFirst -D 1 -N 5\" -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.Bagging -P 100 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.meta.CVParameterSelection -X 10 -S 1 -W weka.classifiers.rules.ZeroR\" -B \"weka.classifiers.meta.FilteredClassifier -F \"weka.filters.supervised.attribute.Discretize -R first-last\" -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.RandomSubSpace -P 0.5 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.meta.RegressionByDiscretization -B 10 -K 0 -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.Stacking -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.ZeroR \"\" -B \"weka.classifiers.rules.DecisionTable -X 1 -S \"weka.attributeSelection.BestFirst -D 1 -N 5\"\" -B \"weka.classifiers.trees.REPTree -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.trees.M5P -M 4.0\" -B \"weka.classifiers.trees.DecisionStump \" -B \"weka.classifiers.rules.ZeroR \" -B \"weka.classifiers.rules.M5Rules -M 4.0\" -B \"weka.classifiers.misc.InputMappedClassifier -I -trainrim -W weka.classifiers.rules.ZeroR\" -B \"weka.classifiers.meta.Vote -S 1 -B \"weka.classifiers.rules.ZeroR \" -R AVG";
    }
    else if (strcmp(alglabel,"bagging"))
    {
        algorithm = "weka.classifiers.meta.Bagging";
        options = " -P 100 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0";
    }
    else if (strcmp(alglabel,"cvparam"))  //CV Parameter selection-- optimizes parameters for any other algorithm
    {
        algorithm = "weka.classifiers.meta.CVParameterSelection";
        options = " -X 10 -S 1 -W weka.classifiers.rules.M5Rules -- -M 4.0";
    }
    else if (strcmp(alglabel,"randomsubspace"))
    {
        const char* algorithm = "weka.classifiers.meta.RandomSubSpace";
        options = " -P 0.5 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0";
    }
    else if (strcmp(alglabel,"regbydiscret"))
    {
        algorithm = "weka.classifiers.meta.RegressionByDiscretization";
        options = " -B 10 -K 0 -W weka.classifiers.trees.J48 -- -C 0.25 -M 2";
    }
    else if (strcmp(alglabel,"stacking"))
    {
        algorithm = "weka.classifiers.meta.Stacking";
        options = " -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.M5Rules -M 4.0\" -B \"weka.classifiers.trees.REPTree -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.trees.M5P -M 4.0\" -B \"weka.classifiers.lazy.LWL -U 0 -K -1 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\" -W weka.classifiers.trees.DecisionStump\" -B \"weka.classifiers.lazy.KStar -B 20 -M a\" -B \"weka.classifiers.lazy.IBk -K 1 -W 0 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\"\" -B \"weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a\" -B \"weka.classifiers.functions.SMOreg -C 1.0 -N 0 -I \"weka.classifiers.functions.supportVector.RegSMOImproved -L 0.001 -W 1 -P 1.0E-12 -train 0.001 -V\" -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.functions.SimpleLinearRegression \" -B \"weka.classifiers.rules.ZeroR \" -B \"weka.classifiers.meta.Bagging -P 100 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.functions.GaussianProcesses -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.meta.RandomSubSpace -P 0.5 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.meta.CVParameterSelection -X 10 -S 1 -W weka.classifiers.rules.ZeroR\" -B \"weka.classifiers.meta.RegressionByDiscretization -B 10 -K 0 -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.Stacking -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.ZeroR \"\" -B \"weka.classifiers.meta.Vote -S 1 -B \"weka.classifiers.rules.ZeroR \" -R AVG\" -B \"weka.classifiers.rules.DecisionTable -X 1 -S \"weka.attributeSelection.BestFirst -D 1 -N 5\"\" -B \"weka.classifiers.trees.DecisionStump \" -B \"weka.classifiers.meta.AttributeSelectedClassifier -E \"weka.attributeSelection.CfsSubsetEval \" -S \"weka.attributeSelection.BestFirst -D 1 -N 5\" -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -train fromCSV.arff -split-percentage 1\"";
    }
    else if (strcmp(alglabel,"vote"))
    {
        algorithm = "weka.classifiers.meta.Vote";
        options = " -S 1 -B \"weka.classifiers.rules.M5Rules -M 4.0\" -B \"weka.classifiers.trees.REPTree -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.trees.M5P -M 4.0\" -B \"weka.classifiers.lazy.LWL -U 0 -K -1 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\" -W weka.classifiers.trees.DecisionStump\" -B \"weka.classifiers.lazy.KStar -B 20 -M a\" -B \"weka.classifiers.lazy.IBk -K 1 -W 0 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\"\" -B \"weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a\" -B \"weka.classifiers.functions.SMOreg -C 1.0 -N 0 -I \"weka.classifiers.functions.supportVector.RegSMOImproved -L 0.001 -W 1 -P 1.0E-12 -train 0.001 -V\" -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.functions.SimpleLinearRegression \" -B \"weka.classifiers.rules.ZeroR \" -B \"weka.classifiers.meta.Bagging -P 100 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.functions.GaussianProcesses -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.meta.RandomSubSpace -P 0.5 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.meta.CVParameterSelection -X 10 -S 1 -W weka.classifiers.rules.ZeroR\" -B \"weka.classifiers.meta.RegressionByDiscretization -B 10 -K 0 -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.Stacking -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.ZeroR \"\" -B \"weka.classifiers.meta.Vote -S 1 -B \"weka.classifiers.rules.ZeroR \" -R AVG\" -B \"weka.classifiers.rules.DecisionTable -X 1 -S \"weka.attributeSelection.BestFirst -D 1 -N 5\"\" -B \"weka.classifiers.trees.DecisionStump \" -B \"weka.classifiers.meta.AttributeSelectedClassifier -E \"weka.attributeSelection.CfsSubsetEval \" -S \"weka.attributeSelection.BestFirst -D 1 -N 5\" -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -train fromCSV.arff -split-percentage 1\"";
    }
    else if (strcmp(alglabel,"inputmapped"))
    {
        algorithm = "weka.classifiers.misc.InputMappedClassifier";
        options = " -I -trainrim -W weka.classifiers.rules.ZeroR";
    }
    else if (strcmp(alglabel,"decisiontable"))
    {
        algorithm = "weka.classifiers.rules.DecisionTable";
        options = "  -X 1 -S \"weka.attributeSelection.BestFirst -D 1 -N 5\"";
    }
    else if (strcmp(alglabel,"m5"))
    {
        algorithm = "weka.classifiers.rules.M5Rules";
        options = " -M 4.0";
    }
    else if (strcmp(alglabel,"zeror"))
    {
        algorithm = "weka.classifiers.rules.ZeroR";
    }
    else if (strcmp(alglabel,"decisionstump"))
    {
        algorithm = "weka.classifiers.trees.DecisionStump";
    }
    else if (strcmp(alglabel,"m5p"))
    {
        algorithm = "weka.classifiers.trees.M5P";
        options = " -M 4.0";
    }
    else if (strcmp(alglabel,"reptree"))
    {
        algorithm = "weka.classifiers.trees.REPTree";
        options = " -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0";
    }

//format for system call: java -classpath ./weka.jar -Xmx512m <algorithm> -train <filenamewithext>.arff > <filenamewithext>.txt
//strcat reference code: http://www.cplusplus.com/reference/clibrary/cstring/strcat/

    strcat (wsyscall,"java -classpath ./weka.jar -Xmx512m ");
    if(argv[getargvindex("-train")] != NULL)
    {
        strcat (wsyscall,algorithm);
        strcat (wsyscall,options);
        strcat (wsyscall," -t ");
        strcat (wsyscall,filenamewithextdotarff.c_str());
        strcat (wsyscall,".arff ");
        //strcat (wsyscall,argv[getargvindex("-train")+1]);
    }
    if(argv[getargvindex("-storemodel")] != NULL)
    {
        strcat (wsyscall,algorithm);
        strcat (wsyscall," -d ");
        strcat (wsyscall,filenamewithextdotarff.c_str());
        strcat (wsyscall,".model ");
        //strcat (wsyscall,argv[getargvindex("-storemodel")+1]);
    }
    if(argv[getargvindex("-loadmodel")] != NULL)
    {
        strcat (wsyscall,algorithm);
        strcat (wsyscall," -l ");
         modelname = argv[getargvindex("-loadmodel")+1];
        strcat (wsyscall,modelname);
        //strcat (wsyscall,argv[getargvindex("-storemodel")+1]);
    }
if(argv[getargvindex("-test")] != NULL)
{
std::string testfile = argv[getargvindex("-test")+1];   //by putting -test and selecting no testfile, automatic cross validation will occur, otherwise the provided testfile will be used
        if (testfile != NULL)
        {

        strcat (wsyscall," -T");
        strcat (wsyscall,testfile);
        }
}
else//if the testfile is not specified, it assumes that there is one located in <modelname without .model>.arff
{
    if(argv[getargvindex("-loadmodel")] != NULL)
    {
std::string testfile = modelname.substr(0,modelname.rfind(".")-1);  //NOTE NEED TO SEE IF THIS TRUNCATES THE NAME BY ONE CHARACTER OR NOT
        strcat(testfile,".arff");
        strcat (wsyscall," -T");
        strcat (wsyscall,);
        std::string modelargv[getargvindex("-loadmodel")+1]
        std::string name = filenamewithext.substr(filenamewithext.rfind("."),1024);
    }
}
    strcat(wsyscall,"-p 0 > _out.txt");
    system(wsyscall);
    return 0;
}
/*
DOCUMENTATION:
usage rtpredict -train TRAININGFILE.EXT \n  Currently supported formats include: \n csv
-train <filename>
-test <testfile>  tests the given model on the data.  If -test is used with no file, 10 fold cross validation will occur.
  If no testfile is specified when a model is loaded via -loadmodel, the model will be tested on a random fold, consisting of 20% of the data contained within <modelname>.arff.
  */
