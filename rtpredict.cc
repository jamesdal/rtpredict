//James Dalgleish
//C++ retention time predictor-- RTPredict
//basic file i/o may resemble tutorial code on: http://www.cprogramming.com/tutorial/c/lesson14.html
/*
#include<iostream>
#include<stdio.h>
#include<iterator>
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
#include <vector>
using namespace std;
using std::ctype;
using std::string;
using std::transform;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cout;
const char ** argvptr;
int argcptr;  //knowledge of copying argv from http://stackoverflow.com/questions/4057961/how-traino-access-argv-from-outside-trainhe-main-function
std::string modelname;
std::string wsyscall = "";

int fieldspos;

bool scanargv(const char* parameter)
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
int getargvindex(const char* parameter)
{
    int i = 0;
    while (i <= argcptr)
    {
        if (strcmp(parameter,argvptr[i])==0)
        {
            return i;
        }

        i++;
    }
    return -1;
}
int getindex(const char* stringtofind, vector<const char*> fields)
{
int i = 0;
std::string stf = stringtofind;
    while (i <= (fields.size() + 1))
    {
        if (stf.compare(fields[i]))
        {
            return i;
        }

        i++;
    }
    return -1;
    }


int countletter(const char* seq, int residue)
{
    int count = 0;
    int i = 0;
    std::string seq_str = seq;
//    std::string residue_str = residue;
    while(i < int(seq_str.length()))
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
const char* countAA(const char* seq)
{
    std::string acid = "ARNDBCEQZGHILKMFPSTWYV";
    std::string counts = "";
    int aapos = 0;
    while (acid[aapos] != '\0')
    {
        const char* aacountwithcomma = "";
        sprintf(const_cast<char*>(aacountwithcomma),"%d,",countletter(seq,acid.at(aapos)));
        counts.append(aacountwithcomma);  //this loop should put counts of all the amino acids right after the sequence
        aapos++;
    }
    return counts.c_str();
}
string reorderline(string line)
{

    return line;
}
int main (int argc,const char *argv[])
{

    argvptr = argv;
    argcptr = argc;
    std::string filenamewithextdotarff;
    std::string filenamewithext = argv[getargvindex("-train")+1];
    std::string ext = filenamewithext.substr(filenamewithext.rfind("."),50);
    std::transform(ext.begin(), ext.end(),  ext.begin(), ::tolower);
    if (scanargv("-train"))
    {
        if (ext.compare("csv"))
        {
            std::string field = "";
            string line;  //some code may resemble samples on http://www.cplusplus.com/doc/tutorial/files/
            ifstream csvfile;
            csvfile.open (argv[getargvindex("-train")+1]);
            std::string filenamewithextdotarff;
            std::string filename = argv[getargvindex("-train")+1];
            std::string dotarff = ".arff";
            filenamewithextdotarff.insert(filenamewithextdotarff.end(), dotarff.begin(), dotarff.end());
            ofstream ArffInputFromCSV(filenamewithextdotarff.c_str());
            ArffInputFromCSV  << "@RELATION ilist\n\n";


            //first line contains the differing fields, so scanning will take place here
            getline(csvfile,line);
            istringstream littlestream (line,istringstream::in);
            vector<const char*> fields;
            while (littlestream.good())
            {
                getline(littlestream,field,',');
                if(strcmp(field.c_str(),"seq")==0)
                {
                    ArffInputFromCSV  << "@ATTRIBUTE seq STRING\n";
                    ArffInputFromCSV  << "@ATTRIBUTE A  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE R  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE N  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE D  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE B  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE C  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE E  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE Q  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE Z  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE G  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE H  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE I  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE L  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE K  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE M  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE F  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE P  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE S  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE T  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE W  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE Y  NUMERIC\n";
                    ArffInputFromCSV  << "@ATTRIBUTE V  NUMERIC\n";//selenocysteine and pyrrolysine removed, add hydrophobicity attribute once calculated
                    fields[fieldspos] = "seq";
                    fieldspos++;
                    fields[fieldspos] = "A";
                    fieldspos++;
                    fields[fieldspos] = "R";
                    fieldspos++;
                    fields[fieldspos] = "N";
                    fieldspos++;
                    fields[fieldspos] = "D";
                    fieldspos++;
                    fields[fieldspos] = "B";
                    fieldspos++;
                    fields[fieldspos] = "C";
                    fieldspos++;
                    fields[fieldspos] = "E";
                    fieldspos++;
                    fields[fieldspos] = "G";
                    fieldspos++;
                    fields[fieldspos] = "H";
                    fieldspos++;
                    fields[fieldspos] = "I";
                    fieldspos++;
                    fields[fieldspos] = "L";
                    fieldspos++;
                    fields[fieldspos] = "K";
                    fieldspos++;
                    fields[fieldspos] = "M";
                    fieldspos++;
                    fields[fieldspos] = "F";
                    fieldspos++;
                    fields[fieldspos] = "P";
                    fieldspos++;
                    fields[fieldspos] = "S";
                    fieldspos++;
                    fields[fieldspos] = "T";
                    fieldspos++;
                    fields[fieldspos] = "W";
                    fieldspos++;
                    fields[fieldspos] = "Y";
                    fieldspos++;
                    fields[fieldspos] = "V";
                    fieldspos++;

                }
                else if(strcmp(field.c_str(),"mz")==0)
                {
                    ArffInputFromCSV  << "@ATTRIBUTE mz  NUMERIC\n";
                    fields[fieldspos] = "mz";
                    fieldspos++;
                }
                else if(strcmp(field.c_str(),"charge")==0)
                {
                    ArffInputFromCSV  << "@ATTRIBUTE charge  NUMERIC\n";
                    fields[fieldspos] = "charge";
                    fieldspos++;
                }
                else if(strcmp(field.c_str(),"intensity")==0)
                {
                    ArffInputFromCSV  << "@ATTRIBUTE intensity  NUMERIC\n";
                    fields[fieldspos] = "intensity";
                    fieldspos++;
                }
                else if(strcmp(field.c_str(),"rt")==0)
                {
                    ArffInputFromCSV  << "@ATTRIBUTE rt  NUMERIC\n\n";
                    fields[fieldspos] = "rt";
                    fieldspos++;
                }
            }
            ArffInputFromCSV  << "@DATA\n";

            //end istringstream of the first line (which contains the column labels)
            int oldorder[4];
            std::string restructured_line = "";

            if (csvfile.good())
            {
                //input file format seq mz intensity charge rt -- on the top row
                //this code restructures the headers of the CSV file
                int mzpos, intensitypos, chargepos, seqpos, rtpos;  //old positions of the given columns on the lines
                getline(csvfile,line);//idea of parsing the individual lines (although that may be one of the intentions when the istreamstring class was written) from post:  http://www.cplusplus.com/forum/general/17771/
                istringstream littlestream (line,istringstream::in);
                int pos = 0;
                while (littlestream.good()) //begin parsing column headings
                {

                    getline(littlestream,field,',');
                    if(strcmp(fields[pos],"seq")==0)
                    {
                        seqpos = pos;
                        const char* seq_tmp = field.c_str();
                        restructured_line.append(field).append(","); //this will append "SEQUENCE," to the line as the first item
                        std::string acid = "ARNDBCEQZGHILKMFPSTWYV";
                        int aapos = 0;
                        while (acid[aapos] != '\0')
                        {
                            const char* aacountwithcomma = "";
                            sprintf(const_cast<char*>(aacountwithcomma),"%d,",countletter(seq_tmp,acid.at(aapos)));
                            restructured_line.append(aacountwithcomma);  //this loop should put counts of all the amino acids right after the sequence
                            aapos++;
                        }
                    }
                    else if (strcmp(fields[pos],"mz")==0 || strcmp(fields[pos],"intensity")==0 || strcmp(fields[pos],"rt")==0 || strcmp(fields[pos],"charge")==0)
                    {
                        restructured_line.append(field).append(",");
                    }
                    pos++;  //increments to the next field, which could be mz, intensity, or charge
                }
                restructured_line.erase(restructured_line.end());
                ArffInputFromCSV << restructured_line << endl;
                cout << restructured_line << endl; //first line (column headers end here)
                //below: takes comma separated values in an old order and then puts into the correct order that the program will expect
                //fields already does this
                while(csvfile.good())//get each line, converts the line to a char* vector, then outputs the line in the order specified by fields using mzpos/chargepos/etc
                {
                    getline(csvfile,line);
                    istringstream vectormaker_line (line, istringstream::in);
                    vector<std::string> lineV;

                    while (vectormaker_line.good())
                    {
                        std::string linetoken = "";
                        getline(vectormaker_line,linetoken,',');
                        lineV.push_back (linetoken);
                    }
                    //reorders the vector according to fields[], then writes it to restructured_line
                    vector<std::string> tmp_V;

                    tmp_V[getindex("seq",fields)] = lineV[seqpos];
                    std::string acid = "ARNDBCEQZGHILKMFPSTWYV";
                    int acidcounter = 0;
                    while (acidcounter < acid.size())
                    {
                        acidcounter++;
                        const char* aaonecharacterstring = acid.substr(acidcounter,1).c_str();
                        tmp_V[getindex(aaonecharacterstring,fields)] = lineV[seqpos + acidcounter];
                     }
                    tmp_V[getindex("mz",fields)] = lineV[mzpos];
                    tmp_V[getindex("charge",fields)] = lineV[chargepos];
                    tmp_V[getindex("intensity",fields)] = lineV[intensitypos];
                    tmp_V[getindex("rt",fields)] = lineV[rtpos];
                    restructured_line = "";
                    //turning tmp_V into a line and writing it to restructured line
                    for (int q = 0; q <= tmp_V.size(); q++)
                     {
                          restructured_line.append(tmp_V[q]).append(",");
                    }
                     restructured_line.erase(restructured_line.end());
            ArffInputFromCSV  << restructured_line; //writes the restructured line to the arff
            restructured_line = ""; //clears the restructured line at the end of each loop
                    /*
                                        i = 0;
                    while (i <= fields.size)
                        if (strcmp(fields[i],"mz")==0)
                        {
                            restructured_line.append(lineV[i]).append(",");
                        }
                    if (strcmp(fields[i],"charge")==0)
                    {
                        restructured_line.append(lineV[i]).append(",");
                    }
                    if (strcmp(fields[i],"intensity")==0)
                    {
                        restructured_line.append(lineV[i]).append(",");
                    }
                    if (strcmp(fields[i],"rt")==0)
                    {
                        restructured_line.append(lineV[i]).append(",");
                    }
                    if (strcmp(fields[i],"seq")==0)
                    {
                        restructured_line.append(lineV[i]).append(",");
                    }
                    */
                }
            }

            ArffInputFromCSV.close();
        }
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
    else
    {
        printf("usage rtpredict -train TRAININGFILE.EXT \n  Currently supported formats include: \n csv");
        return 0;
    }
    /*
    //system("java -classpath ./weka.jar weka.filters.supervised.instance.StratifiedRemoveFolds -i ArffInputFromCSV.arff -o Train.arff -c last -N 4 -F 1 -V");
    //system("java -classpath ./weka.jar weka.filters.supervised.instance.StratifiedRemoveFolds -i ArffInputFromCSV.arff -o Test.arff -c last -N 4 -F 1");

    //system("java -classpath ./weka.jar -Xmx512m weka.classifiers.functions.SMOreg -train ArffInputFromCSV.arff -train ArffInputFromCSV.arff -p 0 -C 1 -N 2 >> results.txt");
    system("java -classpath ./weka.jar -Xmx512m weka.classifiers.rules.M5Rules -M 4.0 -train ArffInputFromCSV.arff -o -split-percentage 1 > wekaoutput.txt");
    //this will run all algorithms... some sort of limiting measure needs to be done, split validation to select the correct one before a real analysis is to take place.
    system("java -classpath ./weka.jar -Xmx512m weka.classifiers.meta.MultiScheme -X 0 -S 1 -B \"weka.classifiers.rules.M5Rules -M 4.0\" -B \"weka.classifiers.trees.REPTree -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.trees.M5P -M 4.0\" -B \"weka.classifiers.lazy.LWL -U 0 -K -1 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\" -W weka.classifiers.trees.DecisionStump\" -B \"weka.classifiers.lazy.KStar -B 20 -M a\" -B \"weka.classifiers.lazy.IBk -K 1 -W 0 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\"\" -B \"weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a\" -B \"weka.classifiers.functions.SMOreg -C 1.0 -N 0 -I \"weka.classifiers.functions.supportVector.RegSMOImproved -L 0.001 -W 1 -P 1.0E-12 -train 0.001 -V\" -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.functions.SimpleLinearRegression \" -B \"weka.classifiers.rules.ZeroR \" -B \"weka.classifiers.meta.Bagging -P 100 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.functions.GaussianProcesses -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.meta.RandomSubSpace -P 0.5 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.meta.CVParameterSelection -X 10 -S 1 -W weka.classifiers.rules.ZeroR\" -B \"weka.classifiers.meta.RegressionByDiscretization -B 10 -K 0 -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.Stacking -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.ZeroR \"\" -B \"weka.classifiers.meta.Vote -S 1 -B \"weka.classifiers.rules.ZeroR \" -R AVG\" -B \"weka.classifiers.rules.DecisionTable -X 1 -S \"weka.attributeSelection.BestFirst -D 1 -N 5\"\" -B \"weka.classifiers.trees.DecisionStump \" -B \"weka.classifiers.meta.AttributeSelectedClassifier -E \"weka.attributeSelection.CfsSubsetEval \" -S \"weka.attributeSelection.BestFirst -D 1 -N 5\" -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -train ArffInputFromCSV.arff -split-percentage 1 -p 0 > wekaoutput.txt");
    */
    const char* alglabel = argv[getargvindex("-a")+1];
    const char* algorithm = "weka.classifiers.meta.MultiScheme";
    const char* options = " -X 0 -S 1 -B \"weka.classifiers.rules.M5Rules -M 4.0\" -B \"weka.classifiers.trees.REPTree -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.trees.M5P -M 4.0\" -B \"weka.classifiers.lazy.LWL -U 0 -K -1 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\" -W weka.classifiers.trees.DecisionStump\" -B \"weka.classifiers.lazy.KStar -B 20 -M a\" -B \"weka.classifiers.lazy.IBk -K 1 -W 0 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\"\" -B \"weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a\" -B \"weka.classifiers.functions.SMOreg -C 1.0 -N 0 -I \"weka.classifiers.functions.supportVector.RegSMOImproved -L 0.001 -W 1 -P 1.0E-12 -train 0.001 -V\" -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.functions.SimpleLinearRegression \" -B \"weka.classifiers.rules.ZeroR \" -B \"weka.classifiers.meta.Bagging -P 100 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.functions.GaussianProcesses -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.meta.RandomSubSpace -P 0.5 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.meta.CVParameterSelection -X 10 -S 1 -W weka.classifiers.rules.ZeroR\" -B \"weka.classifiers.meta.RegressionByDiscretization -B 10 -K 0 -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.Stacking -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.ZeroR \"\" -B \"weka.classifiers.meta.Vote -S 1 -B \"weka.classifiers.rules.ZeroR \" -R AVG\" -B \"weka.classifiers.rules.DecisionTable -X 1 -S \"weka.attributeSelection.BestFirst -D 1 -N 5\"\" -B \"weka.classifiers.trees.DecisionStump \" -B \"weka.classifiers.meta.AttributeSelectedClassifier -E \"weka.attributeSelection.CfsSubsetEval \" -S \"weka.attributeSelection.BestFirst -D 1 -N 5\" -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -train ArffInputFromCSV.arff -split-percentage 1";
    if (strcmp(alglabel,"gaussian"))
    {
        algorithm = "weka.classifiers.functions.GaussianProcesses";
        options = " -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"";
    }
    if (strcmp(alglabel,"best")) {} //this is the default, no explicit declaration is therefore needed here
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
        options = " -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.M5Rules -M 4.0\" -B \"weka.classifiers.trees.REPTree -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.trees.M5P -M 4.0\" -B \"weka.classifiers.lazy.LWL -U 0 -K -1 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\" -W weka.classifiers.trees.DecisionStump\" -B \"weka.classifiers.lazy.KStar -B 20 -M a\" -B \"weka.classifiers.lazy.IBk -K 1 -W 0 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\"\" -B \"weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a\" -B \"weka.classifiers.functions.SMOreg -C 1.0 -N 0 -I \"weka.classifiers.functions.supportVector.RegSMOImproved -L 0.001 -W 1 -P 1.0E-12 -train 0.001 -V\" -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.functions.SimpleLinearRegression \" -B \"weka.classifiers.rules.ZeroR \" -B \"weka.classifiers.meta.Bagging -P 100 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.functions.GaussianProcesses -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.meta.RandomSubSpace -P 0.5 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.meta.CVParameterSelection -X 10 -S 1 -W weka.classifiers.rules.ZeroR\" -B \"weka.classifiers.meta.RegressionByDiscretization -B 10 -K 0 -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.Stacking -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.ZeroR \"\" -B \"weka.classifiers.meta.Vote -S 1 -B \"weka.classifiers.rules.ZeroR \" -R AVG\" -B \"weka.classifiers.rules.DecisionTable -X 1 -S \"weka.attributeSelection.BestFirst -D 1 -N 5\"\" -B \"weka.classifiers.trees.DecisionStump \" -B \"weka.classifiers.meta.AttributeSelectedClassifier -E \"weka.attributeSelection.CfsSubsetEval \" -S \"weka.attributeSelection.BestFirst -D 1 -N 5\" -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -train ArffInputFromCSV.arff -split-percentage 1\"";
    }
    else if (strcmp(alglabel,"vote"))
    {
        algorithm = "weka.classifiers.meta.Vote";
        options = " -S 1 -B \"weka.classifiers.rules.M5Rules -M 4.0\" -B \"weka.classifiers.trees.REPTree -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.trees.M5P -M 4.0\" -B \"weka.classifiers.lazy.LWL -U 0 -K -1 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\" -W weka.classifiers.trees.DecisionStump\" -B \"weka.classifiers.lazy.KStar -B 20 -M a\" -B \"weka.classifiers.lazy.IBk -K 1 -W 0 -A \"weka.core.neighboursearch.LinearNNSearch -A \\\"weka.core.EuclideanDistance -R first-last\\\"\"\" -B \"weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H a\" -B \"weka.classifiers.functions.SMOreg -C 1.0 -N 0 -I \"weka.classifiers.functions.supportVector.RegSMOImproved -L 0.001 -W 1 -P 1.0E-12 -train 0.001 -V\" -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.functions.SimpleLinearRegression \" -B \"weka.classifiers.rules.ZeroR \" -B \"weka.classifiers.meta.Bagging -P 100 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.functions.GaussianProcesses -L 1.0 -N 0 -K \"weka.classifiers.functions.supportVector.PolyKernel -C 250007 -E 1.0\"\" -B \"weka.classifiers.meta.RandomSubSpace -P 0.5 -S 1 -num-slots 1 -I 10 -W weka.classifiers.trees.REPTree -- -M 2 -V 0.001 -N 3 -S 1 -L -1 -I 0.0\" -B \"weka.classifiers.meta.CVParameterSelection -X 10 -S 1 -W weka.classifiers.rules.ZeroR\" -B \"weka.classifiers.meta.RegressionByDiscretization -B 10 -K 0 -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -B \"weka.classifiers.meta.Stacking -X 10 -M \"weka.classifiers.rules.ZeroR \" -S 1 -num-slots 1 -B \"weka.classifiers.rules.ZeroR \"\" -B \"weka.classifiers.meta.Vote -S 1 -B \"weka.classifiers.rules.ZeroR \" -R AVG\" -B \"weka.classifiers.rules.DecisionTable -X 1 -S \"weka.attributeSelection.BestFirst -D 1 -N 5\"\" -B \"weka.classifiers.trees.DecisionStump \" -B \"weka.classifiers.meta.AttributeSelectedClassifier -E \"weka.attributeSelection.CfsSubsetEval \" -S \"weka.attributeSelection.BestFirst -D 1 -N 5\" -W weka.classifiers.trees.J48 -- -C 0.25 -M 2\" -train ArffInputFromCSV.arff -split-percentage 1\"";
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

    wsyscall.append("java -classpath ./weka.jar -Xmx512m ");
    if(getargvindex("-train") != -1)
    {
        wsyscall.append(algorithm);
        wsyscall.append(options);
        wsyscall.append(" -t ");
        wsyscall.append(filenamewithextdotarff.c_str());
        wsyscall.append(".arff ");
        //wsyscall.append(argv[getargvindex("-train")+1]);
    }
    if(getargvindex("-storemodel") != -1)
    {
        wsyscall.append(algorithm);
        wsyscall.append(" -d ");
        wsyscall.append(filenamewithextdotarff.c_str());
        wsyscall.append(".model ");
        //wsyscall.append(argv[getargvindex("-storemodel")+1]);
    }
    if(getargvindex("-loadmodel") != -1)
    {
        wsyscall.append(algorithm);
        wsyscall.append(" -l ");
        modelname = argv[getargvindex("-loadmodel")+1];
        wsyscall.append(modelname);
        //wsyscall.append(argv[getargvindex("-storemodel")+1]);
    }
    if(getargvindex("-test") != -1)
    {
        std::string testfile = argv[getargvindex("-test")+1];   //by putting -test and selecting no testfile, automatic cross validation will occur, otherwise the provided testfile will be used
        if (testfile.c_str() != "")
        {

            wsyscall.append(" -T");
            wsyscall.append(testfile);
        }
    }
    else//if the testfile is not specified, it assumes that there is one located in <modelname without .model>.arff
    {
        if(getargvindex("-loadmodel") != -1)
        {
            std::string testfile = modelname.substr(0,modelname.rfind(".")-1);  //NOTE NEED TO SEE IF THIS TRUNCATES THE NAME BY ONE CHARACTER OR NOT
            testfile.append(".arff");
            wsyscall.append(" -T ");
            wsyscall.append(testfile);
            std::string modelargv = argv[getargvindex("-loadmodel")+1];
            std::string name = filenamewithext.substr(filenamewithext.rfind("."),1024);
        }
    }
    wsyscall.append("-p 0 > _out.txt");
    system(wsyscall.c_str());
    return 0;
}
/*
Retention Time Predictor
usage rtpredict -train TRAININGFILE.EXT \n  Currently supported formats include: \n csv
-train <filename>
-test <testfile>  tests the given model on the data.  If -test is used with no file, 10 fold cross validation will occur.
  If no testfile is specified when a model is loaded via -loadmodel, the model will be tested on a random fold, consisting of 20% of the data contained within <modelname>.arff.
  */
