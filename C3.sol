// SPDX-License-Identifier: MIT
pragma solidity^0.8.18;
contract BankAccount{
    address public owner;
    uint256 public balance;
    constructor(){
        owner=msg.sender;
    }
    modifier onlyOwner(){
        require(msg.sender==owner,"Only the owner can perform this operation");
        _;
    }
    function deposit(uint256 amount) public onlyOwner{
        require(amount > 0,"Amount to be deposited must be greater than 0.");
        balance+=amount;
    }
    function withdraw(uint256 amount) public onlyOwner{
        require(amount > 0,"Amount to be withdrawed must be greater than 0.");
        require(balance >= amount,"Insufficient Balance");
        balance-=amount;
    }
    function getBalance() public view returns (uint256){
        return balance;
    }
}