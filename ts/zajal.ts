namespace React {
  class Element {
    type: (any) => Element;
    props: any;
  }
  
  interface Component {
    mount();
  }
  
  function instantiateComponent(element:Element) {
    var type = element.type;
    if (typeof type === 'function') {
      // User-defined components
      return new CompositeComponent(element);
    } else if (typeof type === 'string') {
      // Platform-specific components
      return new HostComponent(element);
    }  
  }

  class CompositeComponent implements Component {
    currentElement: Element;
    renderedComponent: Component;
    
    constructor(element) {
      this.currentElement = element;
      this.renderedComponent = null;
    }

    mount() {
      var element = this.currentElement;
      var type = element.type;
      var props = element.props;

      var renderedElement = type(props);
      this.renderedComponent = instantiateComponent(renderedElement);

      // Mount the rendered output
      return this.renderedComponent.mount();
    }
  }  
  
  class HostComponent implements Component {
    currentElement: Element;
    renderedChildren: [Component];
    node: any;

    constructor(element) {
      this.currentElement = element;
      this.node = null;
    }

    getPublicInstance() {
      // For DOM components, only expose the DOM node.
      return this.node;
    }

    mount() {
      var element = this.currentElement;
      var type = element.type;
      var props = element.props;
      var children = props.children || [];
      if (!Array.isArray(children)) {
        children = [children];
      }

      // Create and save the node
      var node = document.createElement(type);
      this.node = node;

      // Set the attributes
      Object.keys(props).forEach(propName => {
        if (propName !== 'children') {
          node.setAttribute(propName, props[propName]);
        }
      });

      // Create and save the contained children.
      // Each of them can be a DOMComponent or a CompositeComponent,
      // depending on whether the element type is a string or a function.
      var renderedChildren = children.map(instantiateComponent);
      this.renderedChildren = renderedChildren;

      // Collect DOM nodes they return on mount
      var childNodes = renderedChildren.map(child => child.mount());
      childNodes.forEach(childNode => node.appendChild(childNode));

      // Return the DOM node as mount result
      return node;
    }
  }
}
