

class Checker{
public:
  	// complete this method
    static int comparator(Player a, Player b)  
    {
        if(a.score < b.score) return -1;
        if(a.score == b.score)
        {
            if(a.name > b.name) return -1;
            if(a.name == b.name) return 0;
            if(a.name < b.name) return 1;
        }
        return 1;
    }
};

