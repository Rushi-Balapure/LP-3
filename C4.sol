//SPDX-License-Identifier: MIT
pragma solidity^0.8.18;
contract StudentData{
    struct Student{
        string name;
        uint256 age;
    }
    Student[] public students;

    event StudentAdded(string name,uint256 age);
    event Log(string func, uint256 gas);

    fallback() external payable{
        emit Log("fallback",gasleft());
    }
    receive() external payable {
        emit Log("receive",gasleft());
    }
    function addStudent(string memory _name,uint256 _age)public{
        Student memory newStudent=Student(_name,_age);
        students.push(newStudent);
        emit StudentAdded(_name, _age);
    }
    function getStudentCount() public view returns(uint256){
        return students.length;
    }
    function getStudents(uint256 index)public view returns(string memory,uint256){
        require(index<students.length,"Student does not exist");
        Student memory student=students[index];
        return (student.name,student.age);
    }
}