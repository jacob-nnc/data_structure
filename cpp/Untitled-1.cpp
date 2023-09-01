int reverse(int x) {
        if(abs(x)<10)
            return x;
        uint a=INT_MAX;
        uint b=a+1;
        vector<int>s[3];
        for(int i=a,j=b;i!=0&&j!=0;i/=10,j/=10)
        {
            s[0].push_back(i%10);
            s[1].push_back(j%10);
        }
        for(int i=abs(x);i!=0;i/=10)
        {
            s[2].push_back(i%10);
        }
        if(s[2].size()<s[0].size())
        {
            uint i=0;
            for(int j=0;j<s[2].size();j++)
            {
                i=i*10+s[2][j];
            }
            return x>0?i:-i;
        }
        else if(s[2].size()==s[0].size()&&x>0)
        {
            uint j=0;
            for(int i=0;i<s[0].size();i++)
            {
                if(s[2][i]>s[0][s[0].size()-1-i])
                    return 0;
                j=j*10+s[2][i];
            }
            return j;
        }
        else
        {
            uint j=0;
            for(int i=0;i<s[1].size();i++)
            {
                if(s[2][i]>s[1][s[1].size()-1-i])
                    return 0;
                j=j*10+s[2][i];
            }
            return (int)-j;
        }
    }