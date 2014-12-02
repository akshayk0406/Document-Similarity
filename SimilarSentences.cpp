#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <cmath>

using namespace std;

vector< pair<int,std::vector<int> > > inputData;
std::unordered_map< std::string, int > corpus;
std::unordered_map< std::string, bool > sentenceBucket;
map< pair<int,int> , std::vector<int> > PrefixPosition;

int distinct_words						= 0;
const int sentence_size					= 62000;
const char fname[] 						= "cs341-sentences-08.txt";
//const char fname[] 						= "test.txt";
const double JaccardSimilarity			= 0.9;

bool isSentenceSimilar(std::vector<int> s1,std::vector<int> s2)
{
	int m 	= (int)s1.size();
	int n   = (int)s2.size();

	if(abs(m-n) > 1) return false;

	int skips	= 0;
	if(m == n )
	{
		for (int i = 0; i < m && skips<=1;  i++)
		{
			if(s1[i] != s2[i]) skips++;
		}
		return (skips<=1);
	}
	if(m>n)
	{
		int i = 0,j=0;
		while(i<m && j <n)
		{
			if(s1[i] ==s2[j]){i++;j++;}
			else if(s1[i] != s2[j]){i++;skips++;}
			if (skips>1) return false;
		}
		return true;
	}
	if(n>m)
	{
		int i = 0,j=0;
		while(i<m && j <n)
		{
			if(s1[i] ==s2[j]){i++;j++;}
			else if(s1[i] != s2[j]){j++;skips++;}
			if (skips>1) return false;
		}
		return true;
	}

	return false;
}

bool compareFunction(std::pair<int,std::vector<int> > i,std::pair<int,std::vector<int> > j)
{
	return i.second.size() < j.second.size();
}

void tokenize(char line[] )
{
	
	string str  	= "";
	string sentence = "";
	vector<int> inp;

	char * pch;
	pch 			= strtok (line," ");
	int id 			= -1;	

	while (pch != NULL)
	{
		str = pch; 
		if( corpus.find(str) == corpus.end())	
			corpus[str]	= (++distinct_words);

		if( -1 == id)
		{
			stringstream ss(str);
			ss >> id;
		}
		else
		{
			sentence 		= sentence + str + "::";
			inp.push_back(corpus[str]);
		}
		pch = strtok (NULL," ");
	}
	if(sentenceBucket.find(sentence) == sentenceBucket.end())
	{
		inputData.push_back(make_pair(id,inp));
		sentenceBucket[sentence]	= true;
	}
}

int main()
{
	FILE *fp 		= fopen(fname,"r");
	char str[sentence_size];
	while(fscanf(fp," %[^\n]",str)!=EOF)
		tokenize(str);
	
	fclose(fp);
	sort(inputData.begin(),inputData.end(),compareFunction);
	int prefixLength		= 0;
	for(int i=0;i<inputData.size();i++)
	{
		prefixLength		= floor((double)(1.0-JaccardSimilarity)*inputData[i].second.size())+1;
		for(int j=0;j<prefixLength;j++)
		{
			pair<int,int> P 	= make_pair(inputData[i].second[j],j);
			if(PrefixPosition.find(P) != PrefixPosition.end())
				PrefixPosition[P].push_back(i);
			else
			{
				std::vector<int> idx;
				idx.push_back(i);
				PrefixPosition[P]	= idx;
			}
		}
	}

	for(map< pair<int,int> , std::vector<int> >::iterator it = PrefixPosition.begin() ; it != PrefixPosition.end(); it++ )
    {
            for(int i=0;i<it->second.size();i++)
            {
                    for(int j=i+1;j<it->second.size();j++)
                    {
                    	if((inputData[it->second[i]].first != inputData[it->second[j]].first) && 
                    		isSentenceSimilar(inputData[it->second[i]].second,inputData[it->second[j]].second))
                    		printf("%d %d\n",inputData[it->second[i]].first,inputData[it->second[j]].first );	
                    }
            }
    } 
	

	return 0;
}
