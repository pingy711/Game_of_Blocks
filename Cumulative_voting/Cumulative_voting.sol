pragma solidity ^0.8.2;
pragma abicoder v2;

contract Cumulative_voting{
    
    struct candidate{                                               //stores the details of a candidate
        
        string name;
        address unid;
        uint256 votecount;
        bool ifAuthC;                                               //stores if the candidate has been authorized/records if the candidature has been validated
        
    }
    
    struct voter{                                                   //stores the details of a voter         note:a candidate is NOT a voter by default and vice-versa and needs to register seperately
        
        string name;
        address unid;
        bool ifVoted;
        bool ifAuthV;
        
    }
    
     address private Owner;
    
     modifier isOwner() {                                            //validates if the calling address is same as that of the owner
        require(msg.sender==Owner);
        _;
    }
    
    uint256 public numberOfSeats;                                   //stores how many winners are to be declared
    
    function getnumberOfSeats(uint _numberOfSeats) isOwner public{  //by default it is 1 but the owner can change the value of the numberOfSeats by using this function
        numberOfSeats=_numberOfSeats;
    }      
    
    candidate[] candidateList;
    voter[] voterList;                                                      //list of all voters
    mapping(address=>voter) authVoters;                                     //mapping of authorised voters  note:we are using this even though it causes a bit of data redundancy because accessing elements in a map works faster than an array 
    bool openToVote;                                                        //the next 3 variables decide state of the system and it is controlled by the Owner
    bool nominationsBeingAccepted;
    bool resultDeclared;
    
    constructor() public{
        
        Owner=msg.sender;
        candidateList.push(candidate("NOTA",msg.sender,0,true));            //adds a NOTA as one of the choices for candidature (option zero)
        nominationsBeingAccepted=true;
        openToVote=false;
        resultDeclared=false;
        numberOfSeats=1;
        
    }
    
    function getCandidate(uint location) public view returns(string memory){                //prints the candidate with the index = location, (option number location)
        
        require(nominationsBeingAccepted==false,"List not finalized, try again later");     //works only if the final list of candidates have been decided
        
        require(location<=candidateList.length,"Invalid location");                         
        
        require(candidateList[location].ifAuthC,"Candidate not authenticated");
        
        return(candidateList[location].name);                                               //returns the name of the candidate at index = location
        
    }
    
    function signUpVoter(string memory _name) public{                                       //used by voters to sign up in the system, does not mean they can vote, they can vote only after being authorized
        
        voterList.push(voter(_name,msg.sender,false,false));                                //added to list of unauthorized voters, this list is like a waiting list for authorization and is not used in any other place other than mentioned
         
    }
    
    function signUpCandidate(string memory _name) public{                                   //similar to signUpVoter but the only difference is that candidateList is used everywhere else also along with authorization
        
        require(nominationsBeingAccepted,"Nomination period closed");                       //requires that the Nominations are being accepted
        
        candidateList.push(candidate(_name,msg.sender,0,false));
        
    }
    
    function authoriseVoters() isOwner public{                                              //authorization done by the owner, the body of this function can have other conditions based upon which a potential voter can be gievn the authority to vote
                                                                                            //in this function we directly give authorization wihout any conditions being met
        for(uint256 i=0; i<voterList.length;++i){
            
            if(!voterList[i].ifAuthV){
                
                voterList[i].ifAuthV=true;                                                   
                authVoters[voterList[i].unid]=voterList[i];
            
            }
        }
        
    }
    
    function authoriseCandidates() isOwner public{                                          //same as authoriseVoters
        
        for(uint256 i=0; i<candidateList.length;++i){
            
            if(!candidateList[i].ifAuthC){
                
                candidateList[i].ifAuthC=true;                              
            
            }
        }
        
    }
    
    function closeNominations() isOwner public returns(string memory){                      //the owner can decide when to close accepting nominations for candidature        
        
        nominationsBeingAccepted=false;
        return("Authorize candidates before opening voting");
        
    }
    
    function openVoting() isOwner public{                                                   //the owner can decide when to open the voting process
        
        openToVote=true;
        
    }
    
    function closeVoting() isOwner public{                                                   //the owner can decide when to close the voting process
        
        openToVote=false;
        
    }
    
    function castVote(uint[] memory ballot) public{                                         //function used by the voter to cast their vote, they pass the indices of the candidates they want to vote for after reffering to the getCandidate and getnumberOfSeats as an array
                                                                                            //example input will be if the voter wants to vote for candidates 1 and 3 then the input will be [1,3] or [3,1] (order is irrelevant)        
        require(openToVote,"Voting not opened yet");                                        //voting needs to be opened by the owner
        
        require(ballot.length<=numberOfSeats,"Too many choices, try again");                //correct number of inputs have to be given in the array, if the voter wants to choose NOTA then they can enter 0 as the option
        
        require(!(authVoters[msg.sender].unid==address(0)),"Not authorized to vote");       //voter needs to be authorized by the owner`
        
        require(!authVoters[msg.sender].ifVoted,"Already voted");                           //cannot vote multiple times
        
        
        for(uint256 i=0;i<ballot.length;++i){                                               //adds the votecount of each candidate being voted for
            candidateList[ballot[i]].votecount++;
        }
        
        authVoters[msg.sender].ifVoted=true;
        
    }
    
    string[] winners;                                                                       //stores winners' names
    uint256[] winnerVoteCount;                                                              //stores the list of votecount of winners
    
    function compileResult() isOwner public{                                                //used to compile the results, find the winners and store their details in the winners and winnerVoteCount
        
        openToVote=false;
        uint256 max=0;
        uint256 pos=0;
        
        for(uint256 i=0;i<numberOfSeats;++i){                                               
            
            for(uint256 j=0;j<candidateList.length;++j){
                
                if(max<candidateList[j].votecount){
                    pos=j;
                    max = candidateList[j].votecount;
                }
            
            }
            
            winners.push(candidateList[pos].name);                                      //in case of tie the candidate who registered earliest will win (this is the method used here as tie-breaker, other tie breakers can be added as required)
            winnerVoteCount.push(candidateList[pos].votecount);
            candidateList[pos].votecount=0;
            pos=0;
            max=0;
            
        }
        
        resultDeclared=true;                                                            //changes resultDeclared to true to signify that the general public can now view the results
        
    }
    
    function viewResult() view public returns(string[] memory,uint256[] memory){        //function which anyone can use to view the results
        
        require(resultDeclared,"Result yet to be declared, try again later");
        
        return(winners,winnerVoteCount);
        
    }
    
}