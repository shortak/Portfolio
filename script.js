//We are not using elementbyID since that only works for one instace of that ID
//Instead, use querySelectorAll and change things from there


const dropdownContent = document.querySelectorAll(".dropdown-content");
const button = document.querySelectorAll(".dropbtn");

//To get the element that triggered the event, find the parent; the second child is the drop down menu; toggle the second child
function toggleMenu(event){
    const parentElement = event.target.parentElement;
    const secondChild = parentElement.children[1]; 

    secondChild.classList.toggle('show');
}

function toggleMenuNav(event){
    console.log(document.div);
    const content = event.target.children[0];
    content.classList.toggle('show');
}

 
//Close menu functions

//If the user hovers the menu, then off
dropdownContent.forEach(function(element){  //for each instance of dropdownContent... 
    element.addEventListener('mouseleave', function(){ //add event listener for mouse off...
        element.classList.remove('show'); // which triggers the function to remove show
    });
});

//If the user hovers off the button, call a function
function closeMenu(event) { 

    const parentElement = event.target.parentElement;
    const secondChild = parentElement.children[1];
    
    if(!secondChild.matches(":hover")){
        secondChild.classList.remove("show");
    }
}

const observer = new IntersectionObserver((entries) => {
    entries.forEach((entry) => {
        if (entry.isIntersecting) {
            entry.target.classList.add('fade');
        }else{
            entry.target.classList.remove('fade')
        }
    });
});



const hiddenElements = document.querySelectorAll('.hidden');
hiddenElements.forEach((el) => observer.observe(el));