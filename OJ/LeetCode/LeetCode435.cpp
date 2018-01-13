bool cmp_end(const Interval& a, const Interval& b){
    return a.end < b.end;
}
class Solution {
public:
    
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp_end);
        int count = 0;
        int last = 0;
        for(int i = 1; i < intervals.size(); i++){
            if(intervals[i].start < intervals[last].end){
                count++;
            }else 
                last = i;
        }
        return count;
    }
};