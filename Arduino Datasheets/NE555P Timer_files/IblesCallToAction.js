Ibles.package("Ibles.views", "Ibles.models");

Ibles.signupBannerTemplate = "";
Ibles.signupBannerTemplate += "<div class=\"<< display>> overlay-open\">";
Ibles.signupBannerTemplate += "	<img src=\"\/static\/img\/header\/header-robot.png\"\/>";
Ibles.signupBannerTemplate += "	<p class=\"overlay-message\"> Join Us! <\/p>";
Ibles.signupBannerTemplate += "<\/div>";
Ibles.signupBannerTemplate += "<div class=\"call-to-action << display >> <[ if (display === 'modal') { ]> fade hide <[ } ]>\" data-type=\"type-<< bannerType >>\">";
Ibles.signupBannerTemplate += "    <button type=\"button\" class=\"close alert-close\"><span>×<\/span><\/button>";
Ibles.signupBannerTemplate += "    <div>";
Ibles.signupBannerTemplate += "		<h1><< message >><\/h1>";
Ibles.signupBannerTemplate += "		<p><< subtitle >><\/p>";
Ibles.signupBannerTemplate += "    <\/div>";
Ibles.signupBannerTemplate += "    <div class=\"call-to-action-form\">";
Ibles.signupBannerTemplate += "    <[ if (linkOnly) { ]>";
Ibles.signupBannerTemplate += "		<a href=\"\/account\/register?sourcea=banner&bannerType=<< bannerType >>\" class=\"signup-prompt-submit submit-form btn btn-orange\"><< buttonText >><\/a>";
Ibles.signupBannerTemplate += "    <[ } else { ]>";
Ibles.signupBannerTemplate += "    	<[ if (display !== \"mobile\"){ ]>";
Ibles.signupBannerTemplate += "			<input type=\"email\" class=\"signup-prompt-email form-control\" placeholder=\"Enter email\"\/>";
Ibles.signupBannerTemplate += "			<br\/>";
Ibles.signupBannerTemplate += "			<a href=\"\/account\/register?sourcea=banner&bannerType=<< bannerType >>\" class=\"signup-prompt-submit submit-form btn btn-orange\"><< buttonText >><\/a>";
Ibles.signupBannerTemplate += "		<[ } else { ]>";
Ibles.signupBannerTemplate += "			<div class=\"input-group\">";
Ibles.signupBannerTemplate += "				<input type=\"email\" class=\"signup-prompt-email form-control\" placeholder=\"Enter email\"\/>";
Ibles.signupBannerTemplate += "				<span class=\"input-group-addon submit-form btn btn-orange signup-prompt-submit\"><< buttonText >><\/span>";
Ibles.signupBannerTemplate += "			<\/div>";
Ibles.signupBannerTemplate += "		<[ } ]>";
Ibles.signupBannerTemplate += "    <[ } ]>";
Ibles.signupBannerTemplate += "";
Ibles.signupBannerTemplate += "    <\/div>";
Ibles.signupBannerTemplate += "    <div class=\"call-to-action-robot-img\"><\/div>";
Ibles.signupBannerTemplate += "<\/div>";



Ibles.feedPromptTemplate="";
Ibles.feedPromptTemplate += "    <div class=\"call-to-action << display >> feed-prompt\" data-type=\"type-<< bannerType >>\" style=\"display:block\">";
Ibles.feedPromptTemplate += "        <button type=\"button\" class=\"close alert-close\"><span>×<\/span><\/button>";
Ibles.feedPromptTemplate += "        <div class=\"call-to-action-header\"><\/div>";
Ibles.feedPromptTemplate += "        <div class=\"call-to-action-form\">";
Ibles.feedPromptTemplate += "            <p><< message >><\/p>";
Ibles.feedPromptTemplate += "            <a href=\"\/feed\/customize\/\" class=\"submit-form btn btn-orange customize-feed-link\"><< buttonText >><\/a>";
Ibles.feedPromptTemplate += "        <\/div>";
Ibles.feedPromptTemplate += "    <\/div>";

Ibles.mobileTemplate=""
Ibles.mobileTemplate += "<div class=\"call-to-action fade << display >>\" data-type=\"type-<< bannerType >>\">";
Ibles.mobileTemplate += "	<div class=\"modal-dialog modal-sm\">";
Ibles.mobileTemplate += "		<div class=\"modal-content\">";
Ibles.mobileTemplate += "		    <button type=\"button\" class=\"close alert-close\"><span>×<\/span><\/button>";
Ibles.mobileTemplate += "		    <div>		";
Ibles.mobileTemplate += "				<h1><< message >><\/h1>		";
Ibles.mobileTemplate += "				<p><< subtitle >><\/p>    ";
Ibles.mobileTemplate += "			<\/div>    ";
Ibles.mobileTemplate += "			<div class=\"call-to-action-form\">    ";
Ibles.mobileTemplate += "				<[ if (linkOnly) { ]>";
Ibles.mobileTemplate += "					<a href=\"\/account\/register?sourcea=banner&bannerType=<< bannerType >>\" class=\"signup-prompt-submit submit-form btn btn-orange\"><< buttonText >><\/a>";
Ibles.mobileTemplate += "				<[ } else { ]>";
Ibles.mobileTemplate += "					<[ if (display !== \"mobile\"){ ]>";
Ibles.mobileTemplate += "						<input type=\"email\" class=\"signup-prompt-email form-control\" placeholder=\"Enter email\"\/>			";
Ibles.mobileTemplate += "						<br\/>			";
Ibles.mobileTemplate += "						<a href=\"\/account\/register?sourcea=banner&bannerType=<< bannerType >>\" class=\"signup-prompt-submit submit-form btn btn-orange\"><< buttonText >><\/a>		";
Ibles.mobileTemplate += "					<[ } else { ]>			";
Ibles.mobileTemplate += "						<div class=\"input-group\">				";
Ibles.mobileTemplate += "							<input type=\"email\" class=\"signup-prompt-email form-control\" placeholder=\"Enter email\"\/>				";
Ibles.mobileTemplate += "							<span class=\"input-group-addon submit-form btn btn-orange signup-prompt-submit\"><< buttonText >><\/span>			";
Ibles.mobileTemplate += "						<\/div>		";
Ibles.mobileTemplate += "					<[ } ]>    ";
Ibles.mobileTemplate += "				<[ } ]>    ";
Ibles.mobileTemplate += "			<\/div>    ";
Ibles.mobileTemplate += "			<div class=\"call-to-action-robot-img\"><\/div>";
Ibles.mobileTemplate += "		<\/div>";
Ibles.mobileTemplate += "	<\/div>";
Ibles.mobileTemplate += "<\/div>";

Ibles.views.CallToActionView = Backbone.View.extend({
    events: {
        "click .submit-form":"submitForm",
        "click .close": "close",
        "click .overlay-open":"show",
    },
    close: function(){
        var that = this;
        if (this.model.get('display').indexOf('modal') !== -1 ){
            this.$('.call-to-action').modal('hide');

        } else {
            this.$('.call-to-action').fadeOut(200);
        }
        this.setClosedCookie();

    },
    show: function(){
        if (this.model.get('display').indexOf('modal') !== -1  && $('.modal.in:visible').length === 0){
            this.$('.call-to-action').modal('show')
        } else {
            this.$('.call-to-action').fadeIn(200);
        }
    },
    submitForm: function(){
    },
    setClosedCookie:function(){

    },

    render: function(){
        this.$el.html(this.template(this.model.toJSON()));
        head.load("http://cdn.instructables.com/static/gtm/css/call_to_action.css");
        return this.el;
    }
})

Ibles.models.CallToAction = Backbone.Model.extend({
    defaults:{
        bannerType:"",
        message:"",
        subtitle:"",
        display:"",
        buttonText:"",
        linkOnly:false
    }
})
Ibles.views.SignupPromptView = Ibles.views.CallToActionView.extend({
    template: _.template(Ibles.signupBannerTemplate),
    initialize: function(){
        if (this.model.get('display') === 'mobile modal'){
        //Mobile modals have different templates b/c of Bootstrap 2 vs 3 structures. TODO: fix when transitioned to BS3
            this.template = _.template(Ibles.mobileTemplate)
        }
        this.render();
    },
    submitForm: function(e){
        e.preventDefault();
        var that = this;
        var email = this.$el.find('.signup-prompt-email').val() || "",
            bannerType = this.model.get('bannerType');
        if (email) {
            $.ajax({
                url: "/newsletter/newslettersignup?email="+encodeURIComponent(email),
                method: "GET",
                success: function() {
                    window.location = "/account/register?sourcea=banner&bannerType="+bannerType+"&email="+email;
                }
            });
        } else {
            window.location = "/account/register?sourcea=banner&bannerType="+ bannerType;
        }
    },
    setClosedCookie: function(){
        // show banner once every 30 minutes
			var date = new Date();
			var minutes = 30;
			date.setTime(date.getTime() + (minutes * 60 * 1000));

        $.cookie('SignupPromptClosedBefore', 'true', {path: '/', expires: date});
    }
});
Ibles.views.FeedPrompt = Ibles.views.CallToActionView.extend({
    template: _.template(Ibles.feedPromptTemplate),
    initialize: function(options){
        var cutoff = options.cutoff || 5;
        _.bindAll(this,'render');
        var that = this;
        if (Ibles.session.authenticated()){
            Ibles.API.getRequest('whatDoIFollow')
                .then(function(data){
                    var followed = 0;
                    _.each(_.values(data),function(list){
                        followed = followed + list.length;
                    })
                    if (followed < cutoff){
                        that.render();
                    }

                })
        }
    }
});

Ibles.showSignupPrompt = function(model, delay) {
    var signup_model = new Ibles.models.CallToAction(model)
    var signup_prompt = new Ibles.views.SignupPromptView({model:signup_model});
    $("body").append(signup_prompt.$el);
    setTimeout(function(){
        signup_prompt.show();
    }, delay);
}
Ibles.showFeedPrompt = function(model, delay) {
    var feed_model = new Ibles.models.CallToAction(model);
        var view = new Ibles.views.FeedPrompt({model:feed_model});
        $("body").append(view.$el);

    setTimeout(function(){
        view.show();
    }, delay);
};


