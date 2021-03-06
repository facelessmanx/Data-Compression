#include <bits/stdc++.h>
using namespace std;
struct node
{
    char alphabet[2];
    int frequency;
    struct node *left;
    struct node *right;
};
int t = 0;
int frequency[100];
string alphabet[100];
class compare
{
	public:
    	bool operator()(struct node* n1,struct node* n2) {
        	return n1->frequency>n2->frequency;
    	}
};
priority_queue<struct node*,vector<struct node* >,compare> q;
struct node* newnode(string a,int b)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->alphabet[0] = a[0];
    temp->alphabet[1] = a[1];
    temp->frequency = b;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
string getcode(string line,struct node* root)
{
	if(root->alphabet[0]!='*'&&root->alphabet[1]!='*')
	{
		string code = "";
		code += root->alphabet[0];
		code += root->alphabet[1];
		//cout << root->alphabet[0] << root->alphabet[1] << endl;
		return code; 
	}
	if(line[t]=='0')
	{
		t++;
		return getcode(line,root->left);
	}
	if(line[t]=='1')
	{
		t++;
		return getcode(line,root->right);
	} 
}
void printsymbols(string line,struct node* root)
{
	FILE *fp = fopen("extended_test.txt","w");
	while(t!=line.length())
	{
		string code = getcode(line,root);
		for(int i=0;i<code.length();i++)
		{
			fprintf(fp,"%c",code[i]);
		}
	}
	fclose(fp);
}
int main()
{
	FILE *fp = fopen("huffman_tree.txt","r");
	char c1,c2;
	int n = 0;
	while(fscanf(fp,"%c",&c1)!=EOF)
	{
		fscanf(fp,"%c ",&c2);
		int k = 0;
		fscanf(fp,"%d\n",&k);
		alphabet[n] = "";
		alphabet[n] = alphabet[n]+c1;
		alphabet[n] = alphabet[n]+c2;
		frequency[n] = k;
		n++;
	}
	fclose(fp);
	for(int i=0;i<n;i++)
	{
	    struct node *temp = newnode(alphabet[i],frequency[i]);
		q.push(temp);
	}
	while(q.size()!=1)
	{
		struct node *l = q.top();
		q.pop();
		struct node *r = q.top();
		q.pop();
		int sum = l->frequency + r->frequency;
		struct node *temp = newnode("**",sum);
		temp->left = l;
		temp->right = r;
		q.push(temp);
	}
	struct node *root = q.top();
	q.pop();
	fp = fopen("extended_output.txt","r");
	string line = "";
	while(fscanf(fp,"%c",&c1)!=EOF)
	{
		line += c1;
	}
	fclose(fp);
	printsymbols(line,root);
	return 0;
}
		
			
	
