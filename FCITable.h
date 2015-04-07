#ifndef FCITABLE_H
#define FCITABLE_H

class FCITable;

class FCI{
    
    std::string itemset;
    int    support;
    FCI    *next;
    friend class FCITable;

public:
    FCI(std::string RHSItemset, int RHSSupport){
        
        itemset = RHSItemset;
        support = RHSSupport;
        next    = NULL;
    }
    
    std::string retItemset(){
         
        return itemset;
    }

    int retSupport(){
        
        return support;
    }

    void printFCI(){
        
        std::cout << "( " << itemset << ", " << support << " ) ";
    }
};

class FCITable{
    
    std::vector<FCI*> headList;
    int               numOfHeads;

public:
    FCITable(int RHSNumOfHeads){
        
        headList.resize(RHSNumOfHeads+1, NULL);
        numOfHeads = RHSNumOfHeads;
    }

    void addFCI(std::string itemset, int support){
        
        FCI* FCICursor = headList[ itemset.length() ];

        while( FCICursor ){

            if(FCICursor->itemset == itemset){

                FCICursor->support = (FCICursor->support > support) ? FCICursor->support : support;
                return;
            }

            FCICursor = FCICursor->next;
        }
        
        /*
         * not found in list 
         * add the new FCI to the beginning of the list
         */
        FCI* newFCI = new FCI(itemset, support);

        if( headList[ itemset.length() ] )
            newFCI->next = headList[ itemset.length() ];
                
        headList[ itemset.length() ] = newFCI;
    }
    
    int retNumOfHeads(){

        return numOfHeads;
    }

    void addSubset( FCI& fci, std::vector<int>& subset, int lenOfSubset ){
        
        std::string realItemset("");

        for(int i=lenOfSubset-1 ; i>=0 ; i--)
            realItemset += fci.itemset[ subset[i]-1 ];
        
        addFCI(realItemset, fci.retSupport());
    }

    void genSubset(FCI& fci,int lenOfSubset){

        std::vector<int> subset;

        for(int i=lenOfSubset ; i>0 ; i--)
            subset.push_back( i );
        
        addSubset( fci, subset, lenOfSubset );

        for(int i=0 ; i<lenOfSubset ; ){
            
            if(subset[i] + i < fci.retItemset().length()){

                subset[i] ++;

                for(int j=i-1 ; j>=0 ; j--)
                    subset[j] = subset[j+1] + 1;

                i=0;

                addSubset( fci, subset, lenOfSubset );
            }
            else
                i++;
        }
    }

    void FIRecover(){
        
        for(int i=numOfHeads ; i>0 ; i--){
            
            FCI* FCICursor = headList[ i ];

            while( FCICursor ){

                /* FCIs whose len = 1 have no subsets */
                if(i>1)
                    genSubset(*FCICursor,i-1);

                FCICursor->printFCI();
                FCICursor = FCICursor->next;
            }

            std::cout << std::endl;
        }

    }

    void printFCITable(){
        
        for(int i=1 ; i<=numOfHeads; i++){

            FCI* FCICursor = headList[i];

            while( FCICursor ){

                FCICursor->printFCI();
                FCICursor = FCICursor->next;
            }

            std::cout << std::endl;
        }
    }
    
};

#endif
