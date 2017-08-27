namespace React {
  function mountTree(element: Element, container:HTMLElement) {
    if (container.firstChild) {
      var prevNode = container.firstChild;
      var prevRootComponent: Component = prevNode['_internalInstance'];
      var prevElement = prevRootComponent.currentElement;
      if (prevElement.type == element.type) {
        prevRootComponent.recieve(element);
        return;
      }
      // TODO unmountTree(container)
    }
    var rootComponent = instantiateComponent(element);
    var node = rootComponent.mount();
    container.appendChild(node.getHtmlNode());
    return node;
  }

  function isClass(type): boolean {
    return type.prototype && type.prototype.constructor;
  }

  function instantiateComponent(element: Element): Component {
    if (isClass(element.type)) {
      // Platform-specific components
      return new HostComponent(element);
    } else {
      // User-defined components
      return new CompositeComponent(element);
    }
  }



  // TODO cljs elements?
  class Element {
    type: any;
    props: any;

    constructor(type, props) {
      this.type = type;
      this.props = props;
    }
  }

  interface Component {
    mount(): HostNode;
    unmount(): void;
    getHostNode(): HostNode;
    recieve(nextElement: Element);
    currentElement: Element;
  }

  interface HostNode {
    removeProperty(prop:string);
    setProperty(prop:string, value);
    addChild(child:HostNode);
    replaceChild(child:HostNode,newChild:HostNode);
    removeChild(child:HostNode);
    getHtmlNode():HTMLElement;
  }

  class CompositeComponent implements Component {
    currentElement: Element;
    renderedComponent: Component;

    constructor(element: Element) {
      this.currentElement = element;
      this.renderedComponent = null;
    }

    getHostNode() {
      return this.renderedComponent.getHostNode();
    }

    recieve(nextElement: Element) {
      var prevProps = this.currentElement.props;
      var prevRenderedComponent = this.renderedComponent;
      var prevRenderedElement = prevRenderedComponent.currentElement;

      this.currentElement = nextElement;
      var type = nextElement.type;
      var nextProps = nextElement.props;
      var nextRenderedElement: Element = type(nextProps);

      if (prevRenderedElement.type === nextRenderedElement.type) {
        prevRenderedComponent.recieve(nextRenderedElement);
        return;
      }

      var prevNode = prevRenderedComponent.getHostNode();
      prevRenderedComponent.unmount();
      var nextRenderedComponent = instantiateComponent(nextRenderedElement);
      var nextNode = nextRenderedComponent.mount();

      this.renderedComponent = nextRenderedComponent;
      this.getHostNode().replaceChild(prevNode, nextNode);
      // TODO replace old node with new one, host specific
    }

    mount() {
      var element = this.currentElement;
      var type = this.currentElement.type;
      var props = this.currentElement.props;

      var renderedElement = type(props);
      this.renderedComponent = instantiateComponent(renderedElement);

      return this.renderedComponent.mount();
    }

    unmount() {
      this.renderedComponent.unmount();
    }
  }

  class HostComponent implements Component {
    currentElement: Element;
    renderedChildren: Component[];
    node: HostNode;

    constructor(element: Element) {
      this.currentElement = element;
      this.node = null;
    }

    getHostNode() {
      return this.node;
    }

    recieve(nextElement: Element) {
      var prevChildNode = this.node;
      var prevElement = this.currentElement;
      var prevProps = prevElement.props;
      var nextProps = nextElement.props;
      this.currentElement = nextElement;

      Object.keys(prevProps).forEach(propName => {
        if (propName !== 'children' && !nextProps.hasOwnProperty(propName)) {
          prevChildNode.removeProperty(propName);
        }
      });

      Object.keys(nextProps).forEach(propName => {
        if (propName !== 'children') {
          prevChildNode.setProperty(propName, nextProps[propName]);
        }
      });

      var prevChildren: Element[] = prevProps.children || [];
      if (!Array.isArray(prevChildren)) {
        prevChildren = [prevChildren];
      }
      var nextChildren: Element[] = nextProps.children || [];
      if (!Array.isArray(nextChildren)) {
        nextChildren = [nextChildren];
      }

      var prevRenderedChildren = this.renderedChildren;
      for (var i = 0; i < nextChildren.length; ++i) {
        var prevChild = prevRenderedChildren[i];
        if (!prevChild) {
          var nextChild = instantiateComponent(nextChildren[i]);
          var nextChildNode = nextChild.mount();
          this.node.addChild(nextChildNode); // TODO ADD
          continue;
        }

        var canUpdate = prevChildren[i].type === nextChildren[i].type;
        if (!canUpdate) {
          var prevChildNode = prevChild.getHostNode();
          prevChild.unmount();
          var nextChild = instantiateComponent(nextChildren[i]);
          var nextChildNode = nextChild.mount();
          this.node.replaceChild(prevChildNode, nextChildNode); // TODO REPLACE
          continue;
        }

        prevChild.recieve(nextChildren[i]);
      }

      for (var j = nextChildren.length; j < prevChildren.length; ++j) {
        var prevChild = prevRenderedChildren[j];
        var prevChildNode = prevChild.getHostNode();
        prevChild.unmount();
        this.node.removeChild(prevChildNode); // TODO REMOVE
      }
    }

    mount() {
      var element = this.currentElement;
      var type = element.type;
      var props = element.props;
      var children: Element[] = props.children || [];

      if (!Array.isArray(children)) {
        children = [children];
      }

      var node: HostNode = new type();
      this.node = node;

      Object.keys(props).forEach(propName => {
        if (propName !== 'children')
          node.setProperty(propName, props[propName]);
      });

      var renderedChildren = children.map(instantiateComponent);
      this.renderedChildren = renderedChildren;

      var childNodes = renderedChildren.map(child => child.mount());
      childNodes.forEach(childNode => node.addChild(childNode));

      return node;
    }

    unmount() {
      // TODO do more?
      this.renderedChildren.forEach(child => child.unmount());
    }
  }
}
