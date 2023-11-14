#function receives a string and returns true if it's palindrome otherwise false
def isPalindrome(str):
    return str == str[::-1]

#function receives a string and returns a dictionary with t as a key
#and t length substrings of given string as values if none are found
#function returns an empty dictionary
def get_palindrom_dict(str):
    palindrome_list= []
    palindrome_dict= {}
    for t in range(1, len(str)+1):
        for index in range(0, len(str)):
            if ((index + t) > len(str)):
                continue
            suspected_palindrome= str[index:index+t]
            if (isPalindrome(suspected_palindrome) == True):
                palindrome_list.append(suspected_palindrome)
        if len(palindrome_list) == 0: 
            continue
        palindrome_dict[t]= palindrome_list
        palindrome_list= []
    return palindrome_dict

#function receives a string and returns true if it meets the condition otherwise false
def check_match(str):
    if len(str) == 0:
        return True
    left_str= str[0::2]
    right_str= str[1::2]
    if ((len(left_str)==len(right_str))== False):
        return False
    for i in range(0, len(left_str)):
        for j in range(i+1, len(right_str)):
            if left_str[i] == left_str[j]:
                if right_str[i] != right_str[j]:
                    return False
    return True