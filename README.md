Document-Similarity
===================

This Project address the problem of finding similar documents. 
The Programming assignment of Stanford University CS 341: Advanced Topics in Data Mining: Programming Assignment

Problem Statement:-
Implement an algorithm to find pairs of sentences that are copies or near copies of one another. The goal is to quickly find pairs of sentences that are, at the word level, edit distance at most 1. Edit distance is defined for character strings in Section 3.5.5, but in this exercise you will think of sentences as strings and the words of which they are comprised as the characters. Thus, two sentences S1 and S2 they are at edit distance 1 if S1 can be transformed to S2 by adding, removing, or substituting a single word.

Problem Based on locality-sensitive hashing and Index based methods
Data Size:- 1.6 GB

Algorithm:-

Jaccard's Similarity:-

If S and T are two sets, then Jaccard's Similarity is defined as J = (S intersection T ) / (S Union T).
Consider the strings s = acdefghijk and t = bcdefghijk, and assume J = 0.9. Now we build index on symbol and position of the string within the sentence. That is, let our index have a bucket for each pair (x, i), containing the sentences that have string x in position i of their prefix. Given a sentence s, and assuming J is the minimum desired Jaccard distance, we look at the starting words of s, that is, the positions 1 through floor((1 − J)*L) + 1. If the symbol in position i of the prefix is x, add s to the index bucket for (x, i).

Consider s as a probe sentence.We shall visit the symbols of the prefix of s from the left, and we shall take advantage of the fact that we only need to find a possible matching sentence t if none of the previous buckets we have examined for matches held t. If we find that the ith string of s is x, then we need look in the bucket (x, j) for certain small values of j.

