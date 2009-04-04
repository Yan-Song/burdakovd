#ifndef MACRO_H
#define MACRO_H

#define mset(block,value) memset(block,value,sizeof(block))
#define fo(i,begin,end) for(int i=begin; i<end; i++)
#define foreach(i,x) for(int i=0; i<x.size(); i++)
#define showv(v) foreach(i,v) cout<<v[i]<<" "; cout<<endl
#define ALL(v) v.begin(), v.end()

#endif
