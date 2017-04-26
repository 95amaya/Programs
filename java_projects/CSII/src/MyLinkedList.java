
public class MyLinkedList {
	Node first;

	MyLinkedList(){}
	
	public String getFirst(){//Return String first is pointing to
		return first.getElement();
	}
	
	public String find(String e){// Find String element in Linked List
		Node temp = first;
		String found = "Not Found";
		
		while(temp != null){
			if(temp.getElement() == e)
				found = e;
			temp = temp.getNext();
		}
		return found;
	}
	
	public void addFirst(String e){//rearrange what first is pointing to
		Node newNode = new Node(e);
		
		if(isEmpty())
			first = newNode;
		else{
			newNode.next = first;
			first = newNode;
		}
	}
	
	public void removeFirst(){//Traverse first to first.next
		first = first.getNext();
	}
	
	public int size(){//Return size of Linkied List
		Node temp = first;
		int i = 0;
		while(temp != null){
			i++;
			temp = temp.getNext();
		}
		return i;
	}
	
	public boolean isEmpty(){//Check if LinkedList is Empty
		return first == null;
	}
	
	public void printList(){//Print the List in order of first -> null
		if(isEmpty())
			System.out.println("List is Empty");
		else{
			Node temp = first;
			while(temp != null){
				System.out.print(temp.getElement() + " ");
				temp = temp.getNext();
			}
			System.out.println();
		}
	}
	
}

