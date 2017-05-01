#!/usr/bin/env python
#coding:utf-8
class Solution(object):
    #question 164
    def maximumGap(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)-1
        if n<1:
            return 0
        int_max = sys.maxint
        int_min = -1*sys.maxint

        kmax = [int_min]*n
        kmin = [int_max]*n

        maxium = max(nums)
        minium = min(nums)

        base = max((maxium-minium)/n,1)
        for p in nums:
            t = (p-minium)/(base+1)
            kmax[t] = max(kmax[t],p)
            kmin[t] = min(kmin[t],p)
        if n==1:
            return kmax[0]-kmin[0]
        res = 0
        i=0
        while i<n:
            while i<n and kmax[i]==int_min:
                i +=1
            if i==n:
                break
            tmp = kmax[i]
            i +=1
            while i<n and kmin[i]==int_max:
                i +=1
            if i==n:
                break
            tmp2 = kmin[i]
            res = max(res,tmp2-tmp)
        return res

    #question 165
    def compareVersion(self, version1, version2):
        """
        :type version1: str
        :type version2: str
        :rtype: int
        """
        la = version1.split('.')
        lb = version2.split('.')
        sign = 1
        if len(la)<len(lb):
            tmp = la
            la = lb
            lb = tmp
            sign = -1
        count = 0
        while count<len(lb):
            t1 = int(la[count])
            t2 = int(lb[count])
            if t1>t2:
                return 1*sign
            elif t1<t2:
                return -1*sign
            count +=1

        while count<len(la):
            t = int(la[count])
            if t>0:
                return 1*sign
            count +=1
        return 0
