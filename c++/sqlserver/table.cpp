#ifndef TABLE_CPP
#define TABLE_CPP
#include "macro.hpp"
#include "table.hpp"
#include "exceptions.hpp"
#include <fstream>

vector<string> split(const string& s, const char d)
{
    vector<string> ans;
    int prev=-1;
    do
    {
        int cur=s.find_first_of(d, prev+1);
        ans.push_back(s.substr(prev+1,cur-prev-1));
        prev=cur;
    }
    while (prev!=string::npos);
    return ans;
}

string Table::encode(const string& s)
{
	string ans(s.size()*2,'?');
	for(int i=0; i<s.size(); i++)
	{
		ans[2*i] = 'A' + (s[i]/16);
		ans[2*i+1] = 'A' + (s[i]%16);
	};
	return ans;
}

string Table::decode(const string& s)
{
	string ans(s.size()/2,'?');
	for(int i=0; i<ans.size(); i++)
		ans[i] = 16 * (s[2*i]-'A') + (s[2*i+1]-'A');
	return ans;
}

string Table::vencode(const vector<string>& v)
{
    string ans="";
	vector<string> vans;
	for(int i=0; i<v.size(); i++)
        vans.push_back(encode(v[i]));
    foreach(i,v)
        ans+=(i?";":"")+vans[i];
    return ans;
}

vector<string> Table::vdecode(const string& s)
{
    vector<string> v=split(s,';'),vans;
    for(int i=0; i<v.size(); i++)
        vans.push_back(decode(v[i]));
    return vans;
}

void Table::filenames()
{
    filename=path+"/"+table+".db";
    meta = filename+".meta";
}

Table::Table(string _path, string tablename): path(_path), table(tablename)
// загружаем в память таблицу
{
    filenames();
	
	// read metadata
	ifstream fmeta(meta.c_str(),ios::in);
	if(!fmeta)
		throw TableNotFound();
	string sfields, sfieldtypes;
	fmeta>>sfields>>sfieldtypes;
	fields=vdecode(sfields);
    fieldtypes=vdecode(sfieldtypes);
	fmeta.close();
	
	// read main data
    ifstream fdata(filename.c_str(),ios::in);
    if(!fdata)
        throw TableDataNotFound();
    string encsrow;
    while(fdata>>encsrow)
    {
        vector<string> srow=vdecode(encsrow);
        vector<Field> row;
        foreach(i,srow)
            row.push_back(Field(fieldtypes[i],srow[i]));
        rows.push_back(row);
    }
    fdata.close();
	
}

Table::Table(string _path, string tablename, vector<string> _fields, vector<string> _fieldtypes): path(_path), table(tablename)
{
    fields = _fields;
    fieldtypes = _fieldtypes;
}

void Table::save()
{
    filenames();
    
    // save metadata
    ofstream fmeta(meta.c_str(),ios::out);
    if(!fmeta)
        throw FileError();
    string sfields=vencode(fields),sfieldtypes=vencode(fieldtypes);
    fmeta<<sfields<<endl<<sfieldtypes<<endl;
    fmeta.close();
    
    // save main data
    ofstream fdata(filename.c_str(),ios::out);
    if(!fdata)
        throw FileError();
    foreach(i,rows)
    {
        vector<string> tmp;
        foreach(j,rows[i])
            tmp.push_back(rows[i][j].data);
        fdata<<vencode(tmp)<<endl;
    }
    fdata.close();
}



#endif
