//  In mathematics, economics, and computer science, the stable marriage problem(SMP) is the problem of finding a stable matching between two sets of 
//  elements given a set of preferences for each element.A matching is a mapping from the elements of one set to the elements of the other set.
//  A matching is stable whenever it is not the case that both :
//  a. some given element A of the first matched set prefers some given element B of the second matched set over the element to which A is already matched, and
//  b. B also prefers A over the element to which B is already matched
//  In other words, a matching is stable when there does not exist any alternative pairing(A, B) in which both A and B are individually better off than they would 
//  be with the element to which they are currently matched.
//  The stable marriage problem is commonly stated as :
//  Given n men and n women, where each person has ranked all members of the opposite sex with a unique number between 1 and n in order of preference, 
//  marry the men and women together such that there are no two people of opposite sex who would both rather have each other than their current partners.
//  If there are no such people, all the marriages are "stable".
//  
//  In 1962, David Gale and Lloyd Shapley proved that, for any equal number of men and women, it is always possible to solve the SMP and make all marriages 
//  stable.They presented an algorithm to do so.
//  
//  Algorithm:
//  function stableMatching{
//      Initialize all m ∈ M and w ∈ W to free
//      while ∃ free man m who still has a woman w to propose to{
//          w = m's highest ranked woman to whom he has not yet proposed
//          if w is free
//              (m, w) become engaged
//          else some pair(m', w) already exists
//              if w prefers m to m'
//                  (m, w) become engaged
//                  m' becomes free
//              else
//                 (m', w) remain engaged
//      }    
//  }
//  
//  Similar Problem:
//  The assignment problem seeks to find a matching in a weighted bipartite graph that has maximum weight.Maximum weighted matchings do not have to be stable, but in some applications a maximum weighted matching is better than a stable one.
//  The stable roommates problem is similar to the stable marriage problem, but differs in that all participants belong to a single pool(instead of being divided into equal numbers of "men" and "women").
//  The hospitals / residents problem — also known as the college admissions problem — differs from the stable marriage problem in that the "women" can accept "proposals" from more than one "man" (e.g., a hospital can take multiple residents, or a college can take an incoming class of more than one student).Algorithms to solve the hospitals / residents problem can be hospital - oriented(female - optimal) or resident - oriented(male - optimal).
//  The hospitals / residents problem with couples allows the set of residents to include couples who must be assigned together, either to the same hospital or to a specific pair of hospitals chosen by the couple(e.g., a married couple want to ensure that they will stay together and not be stuck in programs that are far away from each other).The addition of couples to the hospitals / residents problem renders the problem NP - complete.[5]
//  The matching with contracts problem is a generalization of matching problem, in which participants can be matched with different terms of contracts.[6] An important special case of contracts is matching with flexible wages.[7]
